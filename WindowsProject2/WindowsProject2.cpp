#include <stdio.h>
#include <bangtal.h>


SceneID scene1;
ObjectID start, top1, top2, top3, top4, top5;
TimerID timer1;
int ne; char frome;char tmpe; char toe;

int locate[2][5] = {
    {190,190,190,190,190},
    {410,350,290,230,170}
};


ObjectID located(const char* image, SceneID scene, int x, int y, bool shown) {
    ObjectID object = createObject(image);

    locateObject(object, scene, x, y);

    if (shown) {
        showObject(object);
    }
    return object;
}

void toplocate() {
    locateObject(top1, scene1, locate[0][0], locate[1][0]);
    locateObject(top2, scene1, locate[0][1], locate[1][1]);
    locateObject(top3, scene1, locate[0][2], locate[1][2]);
    locateObject(top4, scene1, locate[0][3], locate[1][3]);
    locateObject(top5, scene1, locate[0][4], locate[1][4]);
   
}

void hanoi_tower(int n, char from, char tmp, char to) {
    if (n == 1) {
        ne = n; frome = from; tmpe = tmp; toe = to;
        setTimer(timer1, 0.05f);
        startTimer(timer1);
    }
    else {
        hanoi_tower(n - 1, from, to, tmp);
        ne = n; frome = from; tmpe = tmp; toe = to;
        setTimer(timer1, 0.05f);
        startTimer(timer1);
        
        hanoi_tower(n - 1, tmp, from, to);
    }
}



void Mousecallback(ObjectID obejct, int x, int y, MouseAction action) {
    if (obejct == start) {
        hideObject(start); 
        hanoi_tower(5, 'a', 'b', 'c');
    }
}
void Timercallback(TimerID timer) {
    for (int i = 1; i <= 5; i++) {
        if (ne == i) {
            if (frome == 'a') {
                if (toe == 'b') {
                    locate[0][ne - 1] += 330;
                    toplocate();
                }
                else if (toe == 'c') {
                    locate[0][ne - 1] += 660;
                    toplocate();
                }
            }
            else if (frome == 'b') {
                if (toe == 'a') {
                    locate[0][ne - 1] -= 330;
                    toplocate();
                }
                else if (toe == 'c') {
                    locate[0][ne - 1] += 330;
                    toplocate();
                }
            }
            else if (frome == 'c') {
                if (toe == 'b') {
                    locate[0][ne - 1] -= 330;
                    toplocate();
                }
                else if (toe == 'a') {
                    locate[0][ne - 1] -= 660;
                    toplocate();
                }
            }
        }
    }
}


int main() {
    setTimerCallback(Timercallback);
    setMouseCallback(Mousecallback);

    scene1 = createScene("하노이탑", "하노이탑배경.png");

    start = located("start.png", scene1, 570, 60, true);
    top1 = located("탑1.png", scene1, locate[0][0], locate[1][0], true);
    top2 = located("탑2.png", scene1, locate[0][1], locate[1][1], true);
    top3 = located("탑3.png", scene1, locate[0][2], locate[1][2], true);
    top4 = located("탑4.png", scene1, locate[0][3], locate[1][3], true);
    top5 = located("탑5.png", scene1, locate[0][4], locate[1][4], true);
    timer1 = createTimer();

    startGame(scene1);
}