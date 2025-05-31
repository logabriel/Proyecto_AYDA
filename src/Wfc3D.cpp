#include <Wfc3D.hpp>
#include <tuple>
#include <iostream>
#include <optional>
#include <algorithm>
#include <random>
#include <unordered_set>
#include <queue>

Wfc3D::Wfc3D(
    const std::vector<Object3D> &_patterns,
    const std::vector<double> &_weights,
    std::tuple<int, int, int> size, std::optional<unsigned> custom_seed)
{
    size_x = std::get<0>(size);
    size_y = std::get<1>(size);
    size_z = std::get<2>(size);
    patterns = _patterns;
    weights = _weights;

    rng.seed(std::random_device{}());

    if (custom_seed.has_value())
    {
        rng.seed(custom_seed.value());
    }

    initializeMatrix3D();
}

Wfc3D::~Wfc3D()
{
}

void Wfc3D::createBaseLayer(unsigned int patternId)
{
    for (int x = 0; x < size_x; ++x)
    {
        for (int y = 0; y < size_y; ++y)
        {
            matrix3D[x][y][0] = {patternId};
        }
    }
}

void Wfc3D::initializeMatrix3D() noexcept
{
    matrix3D.resize(size_x, std::vector<std::vector<std::set<unsigned int>>>(size_y, std::vector<std::set<unsigned int>>(size_z)));

    for (int i = 0; i < size_x; ++i)
    {
        for (int j = 0; j < size_y; ++j)
        {
            for (int k = 0; k < size_z; ++k)
            {
                for (unsigned int p = 0; p < patterns.size(); ++p)
                {
                    matrix3D[i][j][k].insert(p); // para cada celda se inicializa con todas las opciones de cubos que esta puede tener
                }
            }
        }
    }
}

// Encuentra la celda con menor entropía
// si hay varias celdas con la misma entropia se escoge una al azar
Coords3DInt Wfc3D::findMinEntropyCell()
{
    int minEntropy = std::numeric_limits<int>::max();
    std::vector<Coords3DInt> minEntropyCells;

    for (int i = 0; i < size_x; ++i)
    {
        for (int j = 0; j < size_y; ++j)
        {
            for (int k = 0; k < size_z; ++k)
            {
                std::set<unsigned int> cell = matrix3D[i][j][k];
                int entropy = cell.size();

                if (entropy > 1)
                {
                    if (entropy < minEntropy)
                    {
                        minEntropy = entropy;
                        minEntropyCells.clear();
                        minEntropyCells.push_back({i, j, k});
                    }
                    else if (entropy == minEntropy)
                    {
                        minEntropyCells.push_back({i, j, k});
                    }
                }
            }
        }
    }

    if (minEntropyCells.empty())
    {
        return {-1, -1, -1}; // Todas las celdas están colapsadas
    }

    std::uniform_int_distribution<size_t> dist(0, minEntropyCells.size() - 1);
    return minEntropyCells[dist(rng)];
}

/**
 * Intenta colapsar una celda en un patrón específico.
 * Si ya se han intentado todos los patrones posibles para esta celda, se devuelve std::nullopt.
 * En caso contrario, se selecciona un patrón al azar (Segun los pesos de probabilidad) de entre las opciones restantes y se colapsa la celda a ese patrón.
 * @param cell la celda a colapsar
 * @return el patrón escogido o std::nullopt si no se pudo colapsar.
 */
std::optional<unsigned> Wfc3D::attemptCollapse(Coords3DInt cell)
{
    auto &currentDecision = decisionStack.top();
    std::set<unsigned int> &cellOptions = matrix3D[cell.x][cell.y][cell.z];

    if (currentDecision.triedPatterns.size() == cellOptions.size())
    {
        return std::nullopt;
    }

    std::vector<unsigned int> remainingOptions;
    std::set_difference(
        cellOptions.begin(), cellOptions.end(),
        currentDecision.triedPatterns.begin(), currentDecision.triedPatterns.end(),
        std::back_inserter(remainingOptions));

    if (remainingOptions.empty())
        return std::nullopt;
    std::vector<double> optionWeights;
    for (unsigned int opt : remainingOptions)
    {
        optionWeights.push_back(weights[opt]);
    }
    std::discrete_distribution<int> dist(optionWeights.begin(), optionWeights.end());
    unsigned int chosen = remainingOptions[dist(rng)];

    currentDecision.triedPatterns.insert(chosen);

    matrix3D[cell.x][cell.y][cell.z] = {chosen};

    return chosen;
}

bool Wfc3D::is3DCompatible(Coords3DInt cell1, Coords3DInt cell2, int pattern1, int pattern2)
{
    auto [x1, y1, z1] = cell1;
    auto [x2, y2, z2] = cell2;

    RelativeDirection direction;
    if (x1 < x2)
        direction = EAST;
    else if (x1 > x2)
        direction = WEST;
    else if (y1 < y2)
        direction = NORTH;
    else if (y1 > y2)
        direction = SOUTH;
    else if (z1 < z2)
        direction = ABOVE;
    else if (z1 > z2)
        direction = BELOW;
    else
        return true;

    const auto &allowed = patterns[pattern1].constraints.get_constraints_for_direction(direction);
    return std::find(allowed.begin(), allowed.end(), pattern2) != allowed.end();
}

struct EntropyComparator
{
    const std::vector<std::vector<std::vector<std::set<unsigned int>>>> &matrix3D;

    EntropyComparator(decltype(matrix3D) &matrix) : matrix3D(matrix) {}

    bool operator()(const Coords3DInt &a, const Coords3DInt &b) const
    {
        return matrix3D[a.x][a.y][a.z].size() > matrix3D[b.x][b.y][b.z].size();
    }
};

std::vector<Coords3DInt> Wfc3D::getNeighbors(int x, int y, int z) const
{
    std::vector<Coords3DInt> neighbors;
    constexpr int directions[6][3] = {
        {1, 0, 0},  // Este
        {-1, 0, 0}, // Oeste
        {0, 1, 0},  // Norte
        {0, -1, 0}, // Sur
        {0, 0, 1},  // Arriba
        {0, 0, -1}  // Abajo
    };

    for (const auto &[dx, dy, dz] : directions)
    {
        int nx = x + dx;
        int ny = y + dy;
        int nz = z + dz;

        if (nx >= 0 && nx < size_x && ny >= 0 && ny < size_y && nz >= 0 && nz < size_z)
        {
            neighbors.emplace_back(Coords3DInt{nx, ny, nz});
        }
    }

    return neighbors;
}

bool Wfc3D::isValidCell(int x, int y, int z) const
{
    return (x >= 0 && x < size_x) &&
           (y >= 0 && y < size_y) &&
           (z >= 0 && z < size_z);
}

/**
 * @brief Propaga las restricciones de un cubo a sus vecinos.
 *
 * Se encarga de propagar las restricciones de un cubo a sus vecinos, es
 * decir, si un cubo ha colapsado a un patrón, se encarga de reducir las
 * posibilidades de los vecinos que no son compatibles con ese patrón.
 *
 * @param cell La celda que se va a propagar
 *
 * @return true si se ha detectado una contradicción, false en caso
 *         contrario
 */
bool Wfc3D::propagateConstraints(Coords3DInt cell)
{
    std::queue<Coords3DInt> queue;
    queue.push(cell);

    while (!queue.empty())
    {
        auto [x, y, z] = queue.front();
        queue.pop();

        if (matrix3D[x][y][z].empty())
        {
            std::cerr << "Contradicción en (" << x << ", " << y << ", " << z << ")\n";
            return true;
        }

        int current_pattern = *matrix3D[x][y][z].begin();

        for (auto [nx, ny, nz] : getNeighbors(x, y, z))
        {
            if (matrix3D[nx][ny][nz].size() == 1)
            {
                continue;
            }

            std::set<unsigned int> new_possibilities;
            for (unsigned int p : matrix3D[nx][ny][nz])
            {
                if (is3DCompatible({x, y, z}, {nx, ny, nz}, current_pattern, p))
                {
                    new_possibilities.insert(p);
                }
            }
            if (matrix3D[nx][ny][nz].empty())
            {
                std::cerr << "No possible result";
                return true;
            }

            if (new_possibilities.size() != matrix3D[nx][ny][nz].size())
            {
                matrix3D[nx][ny][nz] = new_possibilities;
                queue.push({nx, ny, nz});
            }
        }
    }
    return false;
}

void Wfc3D::saveState(const Coords3DInt &cell)
{
    DecisionPoint dp;
    dp.cell = cell;
    dp.history = matrix3D;
    decisionStack.push(dp);
}

bool Wfc3D::backtrack()
{

    if (decisionStack.empty() || attempts >= maxAttempts)
    {
        return false;
    }

    DecisionPoint lastDecision = decisionStack.top();
    decisionStack.pop();

    matrix3D = lastDecision.history;
    attempts++;

    return true;
}

bool Wfc3D::executeWfc3D()
{
    while (attempts < maxAttempts)
    {
        Coords3DInt cell = findMinEntropyCell();

        if (cell.x == -1)
        {
            this->updateRenderVector();
            return true; // todas las celdas han colapsado se detiene el algoritmo
        }

        saveState(cell);
        auto collapsedPattern = attemptCollapse(cell);

        if (!collapsedPattern.has_value())
        {
            if (!backtrack())
            {
                return false;
            }
            continue;
        }

        if (propagateConstraints(cell)) // IF hay contradiccion
        {
            matrix3D = decisionStack.top().history;
            if (!attemptCollapse(cell).has_value())
            {
                if (!backtrack())
                {
                    return false;
                }
            }
        }
    }

    return false;
}

void Wfc3D::printResult() const
{
    for (int z = 0; z < size_z; ++z)
    {
        std::cout << "Capa z = " << z << ":" << std::endl;
        for (int y = 0; y < size_y; ++y)
        {
            for (int x = 0; x < size_x; ++x)
            {
                if (!matrix3D[x][y][z].empty())
                {
                    int pattern = *matrix3D[x][y][z].begin();
                    std::cout << patterns[pattern].id << " ";
                }
                else
                {
                    std::cout << "X ";
                }
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}

void Wfc3D::updateRenderVector()
{

    for (int x = 0; x < size_x; ++x)
    {
        for (int y = 0; y < size_y; ++y)
        {
            for (int z = 0; z < size_z; ++z)
            {
                bool isExterior = false;
                unsigned int patternId = *matrix3D[x][y][z].begin();
                if (patternId == 0)
                {
                    continue; // Si no hay patrón, no se añade al renderVector
                }
                if (
                    x == 0 ||
                    y == 0 ||
                    z == 0 ||
                    x == size_x - 1 ||
                    y == size_y - 1 ||
                    z == size_z - 1)
                {
                    isExterior = true; // Si está en el borde, es exterior
                }
                else
                {
                    for (auto [nx, ny, nz] : getNeighbors(x, y, z))
                    {
                        auto nId = *matrix3D[nx][ny][nz].begin();
                        if (nId == 0)
                        {
                            isExterior = true;
                            break;
                        }
                    }
                }
                if (isExterior)
                {

                    renderVector.emplace_back(std::make_tuple(patternId, x, y, z));
                }
            }
        }
    }
    std::cout << "\tUpdated Render Vector" << std::endl;
}