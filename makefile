CC := g++ -std=c++11
Obj_files = main.o Utrip.o User.o SameType.o Room.o Reserve.o Period.o Hotel.o Comment.o StarFilter.o RoomFilter.o PriceFilter.o CityFilter.o PermissionDenied.o NotEnough.o NotFound.o BadRequest.o InsufficientRatings.o
all: utrip.out
utrip.out: ${Obj_files}
	${CC} ${Obj_files} -o utrip.out
main.o: main.cpp Utrip.hpp
	${CC} -c main.cpp -o main.o
Utrip.o: Utrip.cpp Utrip.hpp Hotel.hpp User.hpp Comment.hpp BadRequest.hpp NotFound.hpp PermissionDenied.hpp CityFilter.hpp RoomFilter.hpp StarFilter.hpp PriceFilter.hpp SameType.hpp
	${CC} -c Utrip.cpp -o Utrip.o
User.o: User.cpp User.hpp Reserve.hpp NotFound.hpp InsufficientRatings.hpp
	${CC} -c User.cpp -o User.o
SameType.o: SameType.cpp SameType.hpp Filter.hpp Rating.hpp
	${CC} -c SameType.cpp -o SameType.o
Room.o: Room.cpp Room.hpp Period.hpp Reserve.hpp
	${CC} -c Room.cpp -o Room.o
Reserve.o: Reserve.cpp Reserve.hpp Room.hpp Period.hpp 
	${CC} -c Reserve.cpp -o Reserve.o
Period.o: Period.cpp Period.hpp 
	${CC} -c Period.cpp -o Period.o
Hotel.o: Hotel.cpp Hotel.hpp Rating.hpp Room.hpp Reserve.hpp Comment.hpp SameType.hpp NotEnough.hpp
	${CC} -c Hotel.cpp -o Hotel.o
Comment.o: Comment.cpp Comment.hpp User.hpp
	${CC} -c Comment.cpp -o Comment.o
StarFilter.o: StarFilter.cpp StarFilter.hpp Filter.hpp Hotel.hpp
	${CC} -c StarFilter.cpp -o StarFilter.o
RoomFilter.o: RoomFilter.cpp RoomFilter.hpp Filter.hpp Hotel.hpp
	${CC} -c RoomFilter.cpp -o RoomFilter.o
PriceFilter.o: PriceFilter.cpp PriceFilter.hpp Filter.hpp Hotel.hpp
	${CC} -c PriceFilter.cpp -o PriceFilter.o
CityFilter.o: CityFilter.cpp CityFilter.hpp Filter.hpp Hotel.hpp
	${CC} -c CityFilter.cpp -o CityFilter.o
InsufficientRatings.o: InsufficientRatings.cpp InsufficientRatings.hpp
	${CC} -c InsufficientRatings.cpp -o InsufficientRatings.o
PermissionDenied.o: PermissionDenied.cpp PermissionDenied.hpp
	${CC} -c PermissionDenied.cpp -o PermissionDenied.o
NotFound.o: NotFound.cpp NotFound.hpp
	${CC} -c NotFound.cpp -o NotFound.o
NotEnough.o: NotEnough.cpp NotEnough.hpp
	${CC} -c NotEnough.cpp -o NotEnough.o
BadRequest.o: BadRequest.cpp BadRequest.hpp
	${CC} -c BadRequest.cpp -o BadRequest.o
clean:
	rm -r *.o