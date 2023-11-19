#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Bod{
    int x, y;
};
struct Poloha{
    Bod theseus;
    Bod minotaur;
};
Bod souradniceMinotaura(Bod theseus, Bod minotaurus, vector<vector<bool>>& mapa) {
    for (int i = 0; i <= 1; i++) {
        Bod novyMinotaurus = {minotaurus.x, minotaurus.y};
        if (minotaurus.x == theseus.x and minotaurus.y == theseus.y) {
            break;
        }
        if (minotaurus.x == theseus.x) {
            novyMinotaurus.y += (theseus.y - minotaurus.y)/(abs(theseus.y - minotaurus.y));
        }
        else if (minotaurus.y == theseus.y) {
            if (minotaurus.y == theseus.y) {
                novyMinotaurus.x += (theseus.x - minotaurus.x)/(abs(theseus.x - minotaurus.x));
            }
        }
        else {
            novyMinotaurus.y += (theseus.y - minotaurus.y)/(abs(theseus.y - minotaurus.y));
            novyMinotaurus.x += (theseus.x - minotaurus.x)/(abs(theseus.x - minotaurus.x));
        }
        minotaurus = novyMinotaurus;
    }
    return minotaurus;
}
int main() {
    int vyska, sirka;
    Bod theseus, minotaur, vychod;
    cin >> sirka >> vyska;
    vector<vector<bool>> mapa(sirka, vector<bool>(vyska, true));
    vector<vector<vector<vector<Poloha>>>> prostor(sirka, vector<vector<vector<Poloha>>>(vyska, vector<vector<Poloha>>(sirka, vector<Poloha>(vyska, {{-1,-1}, {-1, -1}}))));
    for (int y = 0; y < vyska; y++){
        for (int x = 0; x < sirka; x++) {
            int val;
            cin >> val;
            if (val == 1){
                theseus.x = x;
                theseus.y = y;
            }
            if (val == 2) {
                minotaur.y = y;
                minotaur.x = x;
            }
            if (val == 3) {
                vychod.x = x;
                vychod.y = y;
            }
            if (val == 4)
                mapa[x][y] = false;
        }
    }
    queue<Poloha> fronta;
    bool utekl = false;
    fronta.push({theseus.x, theseus.y, minotaur.x, minotaur.y});
    while (not fronta.empty()) {
        Poloha poloha = fronta.front();
        theseus = poloha.theseus;
        minotaur = poloha.minotaur;
        if (theseus.x == vychod.x and theseus.y == theseus.x) {
            utekl = true;
            break;
        }
        fronta.pop();
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++){
                Bod novyTheseus = {theseus.x + i, theseus.y + j};
                if (novyTheseus.x < 0 or novyTheseus.y < 0)
                    continue;
                if (novyTheseus.x >= sirka or novyTheseus.y >= vyska)
                    continue;
                Bod novyMinotaurus = souradniceMinotaura(novyTheseus, minotaur, mapa);
                if (novyTheseus.x == novyMinotaurus.x and novyTheseus.y == novyMinotaurus.y)
                    continue;
                if (prostor[novyTheseus.x][novyTheseus.y][novyMinotaurus.x][novyMinotaurus.y].theseus.x == -1) {
                    prostor[novyTheseus.x][novyTheseus.y][novyMinotaurus.x][novyMinotaurus.y] = {novyTheseus, novyMinotaurus};
                    fronta.push({novyTheseus, novyMinotaurus});
                }
            }
        }
    }
    cout << minotaur.y;
    return 0;
}
