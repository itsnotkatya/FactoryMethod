#include <iostream>

//Интерфейс MovieFactory объявляет операции, которые должны выполнять все подклассы
class MovieFactory {
public:
    ~MovieFactory(){};
    virtual std::string Movie() const = 0;
};

//Подклассы представляют различные реализации интерфейса MovieFactory
class Thriller : public MovieFactory {
public:
    std::string Movie() const override {
        return {"Thriller movie"};
    }
};

class Fantasy : public MovieFactory {
public:
    std::string Movie() const override {
        return {"Fantasy movie"};
    }
};

//класс Movie объявляет фабричный метод, который должен возвращать объект класса MovieFactory
class Movie {
public:
    ~Movie(){};
    virtual MovieFactory* FactoryMethod() const = 0;

    std::string MakeMovie() const {
        MovieFactory* object = this -> FactoryMethod();
        std::string result = "We have made a movie" + object -> Movie();
        delete object;
        return result;
    }
};
//Конкретные подклассы класса Movie изменяют тип полученного продукта
class ThrillerMovie : public Movie {
    MovieFactory* FactoryMethod() const override {
        return new Thriller();
    }
};

class FantasyMovie : public Movie {
    MovieFactory* FactoryMethod() const override {
        return new Fantasy();
    }
};

void Director (const Movie &director) {
    std::cout << director.MakeMovie() << std::endl;
}

int main() {
    Movie* ChristopherNolan = new ThrillerMovie();
    Director(*ChristopherNolan);

    Movie* WesAnderson = new FantasyMovie();
    Director(*WesAnderson);

    delete ChristopherNolan;
    delete WesAnderson;
    return 0;
}