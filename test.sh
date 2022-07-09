#!/bin/bash
find . -type f -name '*.cpp' -exec sed -i 's/using namespace ft;/using namespace std;/g' {} \;
make re && ./a.out $1 > std
find . -type f -name '*.cpp' -exec sed -i 's/using namespace std;/using namespace ft;/g' {} \;
make re && ./a.out $1 > ft
diff --text ft std