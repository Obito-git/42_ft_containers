sed -i -e 's/ ft;/ std;/g' srcs/main.cpp
make re && ./a.out > std
sed -i -e 's/ std;/ ft;/g' srcs/main.cpp
make re && ./a.out > ft
diff ft std