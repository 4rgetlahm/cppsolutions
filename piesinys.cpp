#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

struct Color{
    int RGB[3];
};

struct Rectangle{
    int xPos, yPos;
    int width, height;
    Color color;
};

vector<vector<Color>> updateMap(vector<vector<Color>> _map, Rectangle rectangle){
    for(int i = rectangle.yPos; i != rectangle.height+rectangle.yPos; i++){
        for(int j = rectangle.xPos; j != rectangle.width+rectangle.xPos; j++){
            _map[i][j] = rectangle.color;
        }
    }
    return _map;
}

int main()
{
    freopen("U2.txt", "r", stdin);
    freopen("U2rez.txt", "w", stdout);
    vector<Rectangle> rectanglesVector;
    int _count;
    cin >> _count;
    int maxWidth = -2147483647, maxHeight = -2147483647; // minX = 2147483647, minY = 2147483647;
    for(int i = 0; i != _count; i++){
        Rectangle rectangle;
        cin >> rectangle.xPos >> rectangle.yPos >> rectangle.width >> rectangle.height;
        Color color;
        cin >> color.RGB[0] >> color.RGB[1] >> color.RGB[2];
        rectangle.color = color;
        maxWidth = max(maxWidth, rectangle.xPos+rectangle.width);
        maxHeight = max(maxHeight, rectangle.yPos+rectangle.height);
        rectanglesVector.push_back(rectangle);
    }

    ///IDEJA: pasidaryti 2d zemelapi 100x100 dydzio, nuspalvinti ji baltai, ir tada ant virsaus paisyti tuos staciakampius
    ///Nuo cia piesinys uzpildomas baltais langeliais
    Color white;
    white.RGB[0] = 255;
    white.RGB[1] = 255;
    white.RGB[2] = 255;

    vector<Color> whiteVec;
    for(int i = 0; i != 100; i++){
        whiteVec.push_back(white);
    }
    //vector<vector<Color>> _map(100, vector<Color>(100, white));

    vector<vector<Color>> _map;
    for(int i = 0; i != 100; i++){
        _map.push_back(whiteVec);
    }

    ///atnaujinamas piesinys su kiekvienu staciakampiu
    for(Rectangle &rectangle : rectanglesVector){
        _map = updateMap(_map, rectangle);
    }

    cout << maxHeight << " " << maxWidth << endl;
    for(int i = 0; i != maxHeight; i++){
        for(int j = 0; j != maxWidth; j++){
            cout << _map[i][j].RGB[0] << " " << _map[i][j].RGB[1] << " " << _map[i][j].RGB[2] << endl;
        }
    }

    return 0;
}
