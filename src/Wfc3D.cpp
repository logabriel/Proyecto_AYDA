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

void Wfc3D::initializeMatrix3D() noexcept
{
    matrix3D.resize(size_x, std::vector<std::vector<std::set<unsigned int>>>(size_y, std::vector<std::set<unsigned int>>(size_z)));

    for (size_t i = 0; i < size_x; ++i)
    {
        for (size_t j = 0; j < size_y; ++j)
        {
            for (size_t k = 0; k < size_z; ++k)
            {
                for (size_t p = 0; p < patterns.size(); ++p)
                {
                    matrix3D[i][j][k].insert(p);  // para cada celda se inicializa con todas las opciones de cubos que esta puede tener
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


// Colapsa una celda a un estado específico
int Wfc3D::collapseCell(Coords3DInt cell)
{
    int x = cell.x;
    int y = cell.y;
    int z = cell.z;

    std::vector<int> options(matrix3D[x][y][z].begin(), matrix3D[x][y][z].end());
    std::vector<double> option_weights;

    double total_weight = 0.0;
    for (int opt : options)
    {
        option_weights.push_back(weights[opt]);
        total_weight += weights[opt];
    }

    std::vector<double> probabilities;
    for (double w : option_weights)
    {
        probabilities.push_back(w / total_weight);
    }

    std::discrete_distribution<int> dist(probabilities.begin(), probabilities.end());
    int chosen = options[dist(rng)];

    matrix3D[x][y][z].clear();
    matrix3D[x][y][z].insert(chosen);

    return chosen;
}

bool Wfc3D::is3DCompatible(Coords3DInt cell1, Coords3DInt cell2, int pattern1, int pattern2)
{
    auto [x1, y1, z1] = cell1;
    auto [x2, y2, z2] = cell2;

    if (x1 < x2)
    { // pattern1 a la izquierda de pattern2
        std::vector<unsigned int> list1 = patterns[pattern1].constraints.get_constraints_for_direction(EAST);
        std::vector<unsigned int> list2 = patterns[pattern2].constraints.get_constraints_for_direction(WEST);
        std::unordered_set<int> elementosLista1(list1.begin(), list1.end());

        for (int elemento : list2)
        {
            if (elementosLista1.count(elemento))
            {
                return true; // Hay al menos un elemento en común
            }
        }
        return false;
    }
    else if (x1 > x2)
    { // pattern1 a la derecha de pattern2
        std::vector<unsigned int> list1 = patterns[pattern1].constraints.get_constraints_for_direction(WEST);
        std::vector<unsigned int> list2 = patterns[pattern2].constraints.get_constraints_for_direction(EAST);
        std::unordered_set<int> elementosLista1(list1.begin(), list1.end());
        for (int elemento : list2)
        {
            if (elementosLista1.count(elemento))
            {
                return true; // Hay al menos un elemento en común
            }
        }
        return false;
    }
    else if (y1 < y2)
    { // pattern1 abajo de pattern2
        std::vector<unsigned int> list1 = patterns[pattern1].constraints.get_constraints_for_direction(ABOVE);
        std::vector<unsigned int> list2 = patterns[pattern2].constraints.get_constraints_for_direction(BELOW);
        std::unordered_set<int> elementosLista1(list1.begin(), list1.end());
        for (int elemento : list2)
        {
            if (elementosLista1.count(elemento))
            {
                return true; // Hay al menos un elemento en común
            }
        }
        return false;
    }
    else if (y1 > y2)
    { // pattern1 arriba de pattern2
        std::vector<unsigned int> list1 = patterns[pattern1].constraints.get_constraints_for_direction(BELOW);
        std::vector<unsigned int> list2 = patterns[pattern2].constraints.get_constraints_for_direction(ABOVE);
        std::unordered_set<int> elementosLista1(list1.begin(), list1.end());
        for (int elemento : list2)
        {
            if (elementosLista1.count(elemento))
            {
                return true; // Hay al menos un elemento en común
            }
        }
        return false;
    }
    else if (z1 < z2)
    { // pattern1 detrás de pattern2
        std::vector<unsigned int> list1 = patterns[pattern1].constraints.get_constraints_for_direction(NORTH);
        std::vector<unsigned int> list2 = patterns[pattern2].constraints.get_constraints_for_direction(SOUTH);
        std::unordered_set<int> elementosLista1(list1.begin(), list1.end());
        for (int elemento : list2)
        {
            if (elementosLista1.count(elemento))
            {
                return true; // Hay al menos un elemento en común
            }
        }
        return false;
    }
    else if (z1 > z2)
    { // pattern1 delante de pattern2
        std::vector<unsigned int> list1 = patterns[pattern1].constraints.get_constraints_for_direction(SOUTH);
        std::vector<unsigned int> list2 = patterns[pattern2].constraints.get_constraints_for_direction(NORTH);
        std::unordered_set<int> elementosLista1(list1.begin(), list1.end());
        for (int elemento : list2)
        {
            if (elementosLista1.count(elemento))
            {
                return true; // Hay al menos un elemento en común
            }
        }
        return false;
    }

    return false;
}

struct EntropyComparator {
    const std::vector<std::vector<std::vector<std::set<unsigned int>>>>& matrix3D;

    EntropyComparator(const decltype(matrix3D)& matrix) : matrix3D(matrix) {}

    bool operator()(const Coords3DInt& a, const Coords3DInt& b) const {
        return matrix3D[a.x][a.y][a.z].size() > matrix3D[b.x][b.y][b.z].size();
    }
};

std::vector<Coords3DInt> Wfc3D::getNeighbors(int x, int y, int z) const {
    std::vector<Coords3DInt> neighbors;
    constexpr int directions[6][3] = {
        {1, 0, 0},   // Este
        {-1, 0, 0},  // Oeste
        {0, 1, 0},   // Norte
        {0, -1, 0},  // Sur
        {0, 0, 1},   // Arriba
        {0, 0, -1}   // Abajo
    };

    for (const auto& [dx, dy, dz] : directions) {
        int nx = x + dx;
        int ny = y + dy;
        int nz = z + dz;

        if (nx >= 0 && nx < size_x && ny >= 0 && ny < size_y && nz >= 0 && nz < size_z) {
            neighbors.emplace_back(Coords3DInt{nx, ny, nz});
        }
    }

    return neighbors;
}

bool Wfc3D::isValidCell(int x, int y, int z) const {
    return (x >= 0 && x < size_x) && 
           (y >= 0 && y < size_y) && 
           (z >= 0 && z < size_z);
}

void Wfc3D::propagateConstraints(Coords3DInt cell)
{
    std::queue<Coords3DInt> queue;  
    queue.push(cell);

    while (!queue.empty()) {
        auto [x, y, z] = queue.front();
        queue.pop();

        if (matrix3D[x][y][z].empty()) {
            std::cerr << "Contradicción en (" << x << ", " << y << ", " << z << ")\n";
            return;
        }

        int current_pattern = *matrix3D[x][y][z].begin();

        for (auto [nx, ny, nz] : getNeighbors(x, y, z)) {
            std::set<unsigned int> new_possibilities;
            for (unsigned p : matrix3D[nx][ny][nz]) {
                if (is3DCompatible({x, y, z}, {nx, ny, nz}, current_pattern, p)) {
                    new_possibilities.insert(p);
                }
            }

            if (new_possibilities.size() != matrix3D[nx][ny][nz].size()) {
                matrix3D[nx][ny][nz] = new_possibilities;
                queue.push({nx, ny, nz});
            }
        }
    }
}

bool Wfc3D::executeWfc3D()
{
    while (true)
    {
        Coords3DInt cell = findMinEntropyCell();
        if (cell.x == -1)
        {
            break; // todas las celdas han colapsado se detiene el algoritmo
        }

        collapseCell(cell);
        propagateConstraints(cell);

        bool contradiction = false;
        for (int x = 0; x < size_x && !contradiction; ++x)
        {
            for (int y = 0; y < size_y && !contradiction; ++y)
            {
                for (int z = 0; z < size_z && !contradiction; ++z)
                {
                    if (matrix3D[x][y][z].empty())
                    {
                        contradiction = true;
                    }
                }
            }
        }

        if (contradiction)
        {
            std::cout << "¡Contradicción 3D encontrada!" << std::endl;
            return false;
        }
    }

    return true;
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
