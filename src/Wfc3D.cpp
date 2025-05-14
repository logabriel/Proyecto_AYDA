#include <Wfc3D.hpp>
#include <tuple>
#include <iostream>

Wfc3D::Wfc3D(const std::vector<Object3D> &_patterns, const std::vector<double> &_weights,
             std::tuple<int, int, int> size) : patterns(_patterns), weights(_weights), rng(std::random_device{}())
{
    size_x = std::get<0>(size);
    size_y = std::get<1>(size);
    size_z = std::get<2>(size);

    initializeMatrix3D();
}

void Wfc3D::initializeMatrix3D() noexcept
{
    matrix3D.resize(size_x, std::vector<std::vector<std::set<unsigned>>>(size_y, std::vector<std::set<unsigned>>(size_z)));
    
    for (int i = 0; i < size_x; ++i)
    {
        for (int j = 0; j < size_y; ++j)
        {
            for (int k = 0; k < size_z; ++k)
            {
                for (int id = 0; id < patterns.size(); ++i)
                {
                    matrix3D[i][j][k].insert(i);
                    // Por cada elemento de la matriz le asigno un conjunto de patrones
                    // que pueden estar en esa posición
                    // lo que significa que al principio la entropia es máxima
                    // y todos los patrones son posibles
                }
            }
        }
    }
}

// Encuentra la celda con menor entropía
// si hay varias celdas con la misma entropia se escoje una al azar
std::tuple<int, int, int> Wfc3D::findMinEntropyCell()
{   
    int minEntropy = std::numeric_limits<int>::max();
    std::vector<std::tuple<int, int, int>> minEntropyCells;

    for (int i = 0; i < size_x; ++i) 
    {
        for (int j = 0; j < size_y; ++j) 
        {
            for (int k = 0; k < size_x; ++k) 
            {
                if (matrix3D[i][j][k].size() > 1)
                {
                    if (minEntropy > matrix3D[i][j][k].size())
                    {
                        minEntropy = matrix3D[i][j][k].size();
                        minEntropyCells = {{i, j, k}};
                    }
                    else if (minEntropy == matrix3D[i][j][k].size())
                    {
                        minEntropyCells.emplace_back(i, j, k);
                    }
                }
            }
        }
    }

    if (minEntropyCells.empty()) 
    {
        return {-1, -1, -1}; //cada elemento de la matriz 3d esta colapsado
    }

    std::uniform_int_distribution<size_t> dist(0, minEntropyCells.size() - 1);
    return minEntropyCells[dist(rng)];
}

// Colapsa una celda a un estado específico
int Wfc3D::collapseCell(std::tuple<int, int, int> cell)
{
    int x = std::get<0>(cell);
    int y = std::get<1>(cell);
    int z = std::get<2>(cell);

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
    
    unsigned chosen = options[dist(rng)];
    matrix3D[x][y][z] = {chosen};

    return chosen;
}

bool Wfc3D::is3DCompatible(std::tuple<int, int, int> cell1, std::tuple<int, int, int> cell2, 
    int pattern1, int pattern2)
{
    // Verifica compatibilidad entre cubos adyacentes
    // TODO
}

void Wfc3D::propagate(std::tuple<int, int, int> cell)
{
    // Propaga restricciones a vecinos
    // TODO
}

bool Wfc3D::executeWfc3D()
{   
    // Ejecuta el algoritmo wfc completo
    // TODO
}

void Wfc3D::printMatrix3D() const
{   
    // Imprime la matriz 3D
    // TODO
}

void Wfc3D::toGraphic() const
{   
    // Convierte la matriz a una representación gráfica para vizualización
    // TODO
}