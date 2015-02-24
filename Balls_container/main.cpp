
#include "lib/defines.hpp"
#include "lib/appEnv.hpp"
#include "lib/random.hpp"
#include <ctime>
#include <memory>
#include <vector>

// ウインドウサイズ指定
enum Window {
	WIDTH = 512,
	HEIGHT = 512
};

// 乱数用意
Random random;

// 球の情報を格納
struct Ball{

	Vec2f pos;
	Vec2f size;
	Vec2f speed;
	Color color;
	const float gravity = 5.f;

	enum{ Division = 100 };

	enum Speed_Limit{
		min = -10,
		MAX = 10,
	};
};

// ボールの生成関数
Ball BallCreate(std::shared_ptr<AppEnv> env){ // なんぞこれ。他のやり方あるかなぁ
	// オブジェクト生成
	Ball ball;

	ball.size.x() = 10;
	ball.size.y() = 10;
	ball.pos = env->mousePosition();
	ball.speed.x() = random.fromFirstToLast((float)ball.Speed_Limit::min, (float)ball.Speed_Limit::MAX);
	ball.speed.y() = random.fromFirstToLast((float)ball.Speed_Limit::min, (float)ball.Speed_Limit::MAX);
	ball.color.red() = random.fromFirstToLast(0.5f, 1.f);
	ball.color.green() = random.fromFirstToLast(0.5f, 1.f);
	ball.color.blue() = random.fromFirstToLast(0.5f, 1.f);
	return ball;
}

// 
// メインプログラム
// 
int main() {

	// アプリウインドウの準備
	std::shared_ptr<AppEnv> env;
	env = std::make_unique<AppEnv>(WIDTH, HEIGHT, false, true);

	// 乱数のシードをセット
	random.setSeed(u_int(time(nullptr)));

	std::vector<Ball> ball;

	// メインループ
	while (env->isOpen()) {
		if (env->isPushButton(Mouse::LEFT)){
			ball.push_back(BallCreate(env));
		}


		for (unsigned i = 0; i < ball.size(); ++i){ // ball.size()がunsigned型??

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

		// 描画準備
		env->setupDraw();

		// 球の表示
		for (unsigned i = 0; i < ball.size(); ++i){
			drawFillCircle(ball[i].pos.x(), ball[i].pos.y(),
				ball[i].size.x(), ball[i].size.y(),
				ball[i].Division,
				ball[i].color);
		}

		// 画面更新
		env->update();
	}
}
