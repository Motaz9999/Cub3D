#!/bin/bash
echo "=== TESTING BAD MAPS ==="
for map in maps/bad/*.cub; do
    echo -n "Testing $map: "
    timeout 0.5 ./cub3D "$map" > /dev/null 2>&1
    exit_code=$?
    if [ $exit_code -eq 124 ]; then
        echo "FAIL (Did not exit, probably ran game loop)"
    elif [ $exit_code -eq 0 ]; then
        echo "FAIL (Exited with code 0 instead of error)"
    else
        echo "OK (Exited with error code)"
    fi
done

echo ""
echo "=== TESTING GOOD MAPS ==="
for map in maps/good/*.cub; do
    echo -n "Testing $map: "
    timeout 0.5 ./cub3D "$map" > /dev/null 2>&1
    exit_code=$?
    if [ $exit_code -eq 124 ]; then
        echo "OK (Ran properly / timeout hit)"
    elif [ $exit_code -eq 0 ]; then
        echo "OK (Exited with code 0)"
    else
        echo "FAIL (Exited with error code: $exit_code)"
    fi
done
