
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
	} ball;

	// 球の情報を確立
	ball.size.x() = 10;
	ball.size.y() = 10;
	ball.pos.x() = random.fromFirstToLast((float)-WIDTH / 2, WIDTH / 2 - ball.size.x());
	ball.pos.y() = random.fromFirstToLast((float)-HEIGHT / 2, HEIGHT / 2 - ball.size.y());
	ball.speed.x() = random.fromFirstToLast((float)ball.Speed_Limit::min, (float)ball.Speed_Limit::MAX);
	ball.speed.y() = random.fromFirstToLast((float)ball.Speed_Limit::min, (float)ball.Speed_Limit::MAX);
	ball.color.red() = random.fromFirstToLast(0.5f, 1.f);
	ball.color.green() = random.fromFirstToLast(0.5f, 1.f);
	ball.color.blue() = random.fromFirstToLast(0.5f, 1.f);

	// メインループ
	while (env->isOpen()) {

		// Gを押したら重力をかける
		if (env->isPressKey('G')){
			ball.speed.y() -= ball.gravity;
		}

		// 球の位置を更新
		ball.pos += ball.speed;

		// 壁に球が当たったら跳ね返らせる
		if (ball.pos.x() < -WIDTH / 2){
			ball.pos.x() = -WIDTH / 2;
			ball.speed.x() *= -1.f;
		}
		if (ball.pos.x() > WIDTH / 2){
			ball.pos.x() = WIDTH / 2;
			ball.speed.x() *= -1.f;
		}
		if (ball.pos.y() > HEIGHT / 2){
			ball.pos.y() = HEIGHT / 2;
			ball.speed.y() *= -1.f;
		}
		if (ball.pos.y() < -HEIGHT / 2){
			ball.pos.y() = -HEIGHT / 2;
			ball.speed.y() *= -1.f;
		}
		
	const int Division = 100;

	// 描画準備
    env->setupDraw(); 

	// 球の表示
	drawFillCircle(ball.pos.x(), ball.pos.y(), ball.size.x(), ball.size.y(), Division, ball.color);

	// 画面更新
    env->update();
  }
}
