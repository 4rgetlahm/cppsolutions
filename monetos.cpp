#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

struct Coin{
    int mass = 0; int price = 0;
};

struct Node{
    int mass = 0; int price = 0;
    bool unusable = false;
};

bool customSort(Node first, Node second){
    if(first.price < second.price) return true;
    return false;
}

bool customUnique(Node first, Node second){
    if(first.price == second.price) return true;
    return false;
}

vector<Node> generateNodes(vector<Node> &nodeList, vector<Coin> coinData, int max_weight, int &minPrice, int &maxPrice, vector<int> &priceData){
    bool update = false;
    vector<Node> newNodes;
    for(Node &node : nodeList){
        if(node.mass > max_weight){
            node.unusable = true;
        }
        if(!node.unusable){
            for(Coin &coin : coinData){
                Node newNode;
                newNode.mass = node.mass + coin.mass;
                newNode.price = node.price + coin.price;
                if(newNode.mass == max_weight){
                    if(newNode.price < minPrice){
                        minPrice = newNode.price;
                    }
                    if(newNode.price > maxPrice){
                        maxPrice = newNode.price;
                    }
                }
                else if(newNode.mass < max_weight && !(find(priceData.begin(), priceData.end(), newNode.price) != priceData.end())){
                    newNodes.push_back(newNode);
                    priceData.push_back(newNode.price);
                    update = true;
                }
            }
        }
    }
    nodeList.clear();
    if(update){
        sort(newNodes.begin(), newNodes.end(), customSort);
        newNodes.erase( unique( newNodes.begin(), newNodes.end(), customUnique ), newNodes.end() );
        generateNodes(newNodes, coinData, max_weight, minPrice, maxPrice, priceData);
    }
}

int main() {
    freopen("duota.txt", "r", stdin);
    freopen("rezultatai.txt", "w", stdout);
    vector<Coin> coinData;
    vector<int> priceData;
    int max_weight, coin_count, minPrice = 2147483646, maxPrice = -2147483647;
    cin >> max_weight >> coin_count;
    for(int i = 0; i != coin_count; i++){
        Coin currentCoin;
        cin >> currentCoin.price >> currentCoin.mass;
        coinData.push_back(currentCoin);
    }
    vector<Node> firstTree;
    for(Coin &coin : coinData){
        Node currentNode;
        currentNode.mass = coin.mass;
        currentNode.price = coin.price;
        firstTree.push_back(currentNode);
    }
    generateNodes(firstTree, coinData, max_weight, minPrice, maxPrice, priceData);
    cout << minPrice << " " << maxPrice << endl;
    return 0;
}
