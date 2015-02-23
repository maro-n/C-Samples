
#include "lib/defines.hpp"
#include "lib/appEnv.hpp"
#include "lib/random.hpp"
#include <ctime>
#include <memory>

enum Window {
  WIDTH  = 512,
  HEIGHT = 512
};

// 
// メインプログラム
// 
int main() {
	// アプリウインドウの準備
	std::unique_ptr<AppEnv> env;
	env = std::make_unique<AppEnv>(WIDTH, HEIGHT, false, true);

	// 乱数用意
	Random random;
	random.setSeed(u_int(time(nullptr)));

	// 球の情報を格納
	struct Ball{
		Vec2f pos;
		Vec2f size;
		Vec2f speed;
		Color color;
		float gravity = 5.f;

		enum Speed_Limit{
			min = -10,
			MAX =  10,
		};
	};

	enum  { Ball_Max = 5 };

	Ball ball[Ball_Max];

	// 球の情報を確立
	for (int i = 0; i < Ball_Max; ++i){
		ball[i].size.x() = 10;
		ball[i].size.y() = 10;
		ball[i].pos.x() = random.fromFirstToLast((float)-WIDTH / 2, WIDTH / 2 - ball[i].size.x());
		ball[i].pos.y() = random.fromFirstToLast((float)-HEIGHT / 2, HEIGHT / 2 - ball[i].size.y());
		ball[i].speed.x() = random.fromFirstToLast((float)ball[i].Speed_Limit::min, (float)ball[i].Speed_Limit::MAX);
		ball[i].speed.y() = random.fromFirstToLast((float)ball[i].Speed_Limit::min, (float)ball[i].Speed_Limit::MAX);
		ball[i].color.red() = random.fromFirstToLast(0.5f, 1.f);
		ball[i].color.green() = random.fromFirstToLast(0.5f, 1.f);
		ball[i].color.blue() = random.fromFirstToLast(0.5f, 1.f);
	}
	// メインループ
	while (env->isOpen()) {
		for (int i = 0; i < Ball_Max; ++i){
			// Gを押したら重力をかける
			if (env->isPressKey('G')){
				ball[i].speed.y() -= ball[i].gravity;
			}

			// 球の位置を更新
			ball[i].pos += ball[i].speed;

			// 壁に球が当たったら跳ね返らせる
			if (ball[i].pos.x() < -WIDTH / 2){
				ball[i].pos.x() = -WIDTH / 2;
				ball[i].speed.x() *= -1.f;
			}
			if (ball[i].pos.x() > WIDTH / 2){
				ball[i].pos.x() = WIDTH / 2;
				ball[i].speed.x() *= -1.f;
			}
			if (ball[i].pos.y() > HEIGHT / 2){
				ball[i].pos.y() = HEIGHT / 2;
				ball[i].speed.y() *= -1.f;
			}
			if (ball[i].pos.y() < -HEIGHT / 2){
				ball[i].pos.y() = -HEIGHT / 2;
				ball[i].speed.y() *= -1.f;
			}
		}
		
	const int Division = 100;

	// 描画準備
    env->setupDraw(); 

	// 球の表示
	for (int i = 0; i < Ball_Max; ++i){
		drawFillCircle(ball[i].pos.x(), ball[i].pos.y(), ball[i].size.x(), ball[i].size.y(), Division, ball[i].color);
	}

	// 画面更新
    env->update();
  }
}
