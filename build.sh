# Cleaning...
rm -rf ./out
mkdir out

cd out
cmake -G"Unix Makefiles" ..
make

cd ..
