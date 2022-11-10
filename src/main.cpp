#include <M5StickCPlus.h>


float accX = 0.0F;
float accY = 0.0F;
float accZ = 0.0F;
float gyroX = 0.0F;
float gyroY = 0.0F;
float gyroZ = 0.0F;
float pitch = 0.0F;
float roll  = 0.0F;
float yaw   = 0.0F;

// https://qiita.com/foka22ok/items/53d5271a21313e9ddcbd

float stockedGyroZs[10];
int stockCnt=0;
float adjustGyroZ=0;
int stockedGyroZLength=0;


void freq(int f, int t) {
    M5.Beep.tone(f, t);
    delay(t);
    M5.Beep.mute();
    delay(t);
}


void setup() {
    // start M5Stack
    M5.begin();
    stockedGyroZLength=sizeof(stockedGyroZs)/sizeof(int);
    M5.Lcd.setTextFont(2);
    M5.IMU.Init();
    M5.Beep.setVolume(7);
}


void loop() {
    M5.update();
    M5.Lcd.fillScreen(BLACK);

    M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);
    M5.IMU.getAccelData(&accX, &accY, &accZ);
    // M5.IMU.getAhrsData(&pitch, &roll, &yaw);
    
    if (stockCnt<stockedGyroZLength) {
        stockedGyroZs[stockCnt] = gyroZ;
        stockCnt++;
    } else {
        if (adjustGyroZ == 0) {
            for (int i = 0; i < stockedGyroZLength; i++) {
                adjustGyroZ += stockedGyroZs[i] / stockedGyroZLength;
            }
        }
        //貯めたデータの平均値を使ってgyroZを補正する
        gyroZ -= adjustGyroZ; 
        //ここでaccelデータと補正したgyroデータを使ってpitch・roll・yawを計算する
        MahonyAHRSupdateIMU(gyroX * DEG_TO_RAD, gyroY * DEG_TO_RAD, gyroZ * DEG_TO_RAD, accX, accY, accZ, &pitch, &roll, &yaw);
    }

    M5.Lcd.setCursor(0, 0);
    M5.Lcd.println();
    M5.Lcd.printf("  gyroX = %6.2f\n", gyroX);
    M5.Lcd.printf("  gyroY = %6.2f\n", gyroY);
    M5.Lcd.printf("  gyroZ = %6.2f\n", gyroZ);
    M5.Lcd.println();
    M5.Lcd.printf("  accX = %5.2f\n", accX);
    M5.Lcd.printf("  accY = %5.2f\n", accY);
    M5.Lcd.printf("  accZ = %5.2f\n", accZ);
    M5.Lcd.println();
    M5.Lcd.printf("  pitch = %5.2f\n", pitch);
    M5.Lcd.printf("  roll = %5.2f\n", roll);
    M5.Lcd.printf("  yaw = %5.2f\n", yaw);

    if (M5.BtnA.wasPressed()) {
        freq(740, 150);
        freq(587, 150);
        freq(440, 150);
        freq(587, 150);
        freq(659, 150);
        freq(880, 300);
        freq(440, 150);
        freq(659, 150);
        freq(740, 150);
        freq(650, 150);
        freq(440, 150);
        freq(587, 450);
    } else if (M5.BtnB.wasPressed()) {
        freq(880, 100); // la
        freq(880, 200); // la
        freq(988, 100);
        freq(880, 100);
        freq(740, 100);
        freq(880, 200);
        
        freq(880, 100); // la
        freq(880, 200); // la
        freq(988, 100);
        freq(880, 100);
        freq(740, 100);
        freq(880, 200);

        freq(587, 100);
        freq(587, 100);
        freq(587, 100);
        freq(659, 100);
        freq(740, 300);
        freq(587, 100);
        freq(740, 300);
        freq(880, 100);
        freq(880, 400);
        
        freq(587, 100);
        freq(587, 100);
        freq(587, 100);
        freq(659, 100);
        freq(740, 400);
        freq(587, 100);
        freq(587, 100);
        freq(587, 100);
        freq(659, 100);
        freq(740, 400);

        freq(659, 100);
        freq(659, 100);
        freq(659, 100);
        freq(587, 100);
        freq(659, 200);
        freq(740, 200);
        freq(880, 200);
        freq(784, 200);
        freq(740, 200);
        freq(659, 200);

        freq(880, 100); // la
        freq(880, 200); // la
        freq(988, 100);
        freq(880, 100);
        freq(740, 100);
        freq(880, 200);
        
        freq(880, 100); // la
        freq(880, 200); // la
        freq(988, 100);
        freq(880, 100);
        freq(740, 100);
        freq(659, 200);
        freq(587, 400);
    }
    delay(1000);
}