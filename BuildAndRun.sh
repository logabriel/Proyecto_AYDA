clear
rm build/ProyectoWFC
rm build/tests
cmake -B build && cmake --build build &&
if [ "$#" -ne 4 ]; then
    echo "Usage: ./BuildAndTest.sh <x> <y> <z> <seed>\n"
    exit 1
fi
./build/ProyectoWFC $1 $2 $3 $4