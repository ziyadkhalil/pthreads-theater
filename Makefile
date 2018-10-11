build: ./build/main.o ./build/seat.o ./build/seller.o ./build/time.o ./build/low_seller.o ./build/mid_seller.o ./build/high_seller.o
	@g++ -pthread -Wall ./build/main.o ./build/seller.o ./build/time.o ./build/low_seller.o ./build/mid_seller.o ./build/high_seller.o  ./build/seat.o -o pthreads-theater 


./build/main.o: ./src/main.cpp
	@mkdir -p ./build
	g++ -c ./src/main.cpp -o ./build/main.o

./build/seller.o: ./src/sellers_package/seller.cpp ./src/sellers_package/seller.h
	g++ -c ./src/sellers_package/seller.cpp   -o ./build/seller.o

./build/time.o: ./src/time_sync/time.cpp ./src/time_sync/time.h
	g++ -c  ./src/time_sync/time.cpp  -o ./build/time.o

./build/low_seller.o: ./src/sellers_package/low_seller.cpp ./src/sellers_package/seller.h
	g++ -c ./src/sellers_package/low_seller.cpp -o ./build/low_seller.o

./build/mid_seller.o: ./src/sellers_package/mid_seller.cpp ./src/sellers_package/seller.h
	g++ -c ./src/sellers_package/mid_seller.cpp -o ./build/mid_seller.o

./build/high_seller.o: ./src/sellers_package/high_seller.cpp ./src/sellers_package/seller.h
	g++ -c ./src/sellers_package/high_seller.cpp -o ./build/high_seller.o

./build/seat.o: ./src/sellers_package/seat.cpp ./src/sellers_package/seller.h
	g++  -c  ./src/sellers_package/seat.cpp -o ./build/seat.o

clean:
	@rm -f ./build/*.o 

run:
	./output	


