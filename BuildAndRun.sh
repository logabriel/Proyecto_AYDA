clear
rm build/ProyectoWFC
rm build/tests
cmake -B build && 
cmake --build build && clear
if [ "$#" -eq 4 ]; then
    time ./build/ProyectoWFC $1 $2 $3 $4
#fi
else
    echo "Usage: ./BuildAndRun.sh <x> <y> <z> <seed>"
    exit 1
fi
# time ./build/ProyectoWFC $1 $2 $3 $4