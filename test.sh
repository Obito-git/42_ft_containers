find . -type f -name '*.cpp' -exec sed -i 's/using namespace ft;/using namespace std;/g' {} \;
make re && ./a.out > std
find . -type f -name '*.cpp' -exec sed -i 's/using namespace std;/using namespace ft;/g' {} \;
make re && ./a.out > ft
diff ft std
