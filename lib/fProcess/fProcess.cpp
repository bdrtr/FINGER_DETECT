#include "fProcess.h"
#include <Adafruit_Fingerprint.h>
#include <Arduino.h>



fProcess::fProcess() {

};

void fProcess::Initialize() {

}

void fProcess::delDB() {

    Adafruit_Fingerprint finger = Adafruit_Fingerprint(&Serial2);
    finger.emptyDatabase();   
}

void fProcess::enRoll(uint16_t id) {


    Adafruit_Fingerprint finger = Adafruit_Fingerprint(&Serial2);
    finger.begin(57600);

    int data = -1;
    Serial.print("Parmak izi şu kullanıcı için bekleniyor # "); Serial.println(id);
    while (data != FINGERPRINT_OK) {
        data = finger.getImage();
        switch (data) {
        case FINGERPRINT_OK:
        Serial.println("Parmak izi alındı ");
        break;
        case FINGERPRINT_NOFINGER:
        Serial.print(".");
        break;
        case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println("Bağlantı hatası");
        break;
        case FINGERPRINT_IMAGEFAIL:
        Serial.println("Hatalı resim");
        break;
        default:
        Serial.println("Bir hata meydana geldi");
        break;
        }
    }


    data = finger.image2Tz(1);
    switch (data) {
        case FINGERPRINT_OK:
        Serial.println("Resim dönüştürüldü");
        break;
        case FINGERPRINT_IMAGEMESS:
        Serial.println("Resim belirsiz");
        return;
        case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println("Bağlantı hatası");
        return;
        case FINGERPRINT_FEATUREFAIL:
        Serial.println("Parmak izinin nitelikleri belirgin değil");
        return;
        case FINGERPRINT_INVALIDIMAGE:
        Serial.println("Parmak izi niteliği anlaşılamadı");
        return;
        default:
        Serial.println("Hata");
        return;
    }

    Serial.println("Yeniden girmeye hazır");
    delay(50);
    data = 0;
    while (data != FINGERPRINT_NOFINGER) {
        data = finger.getImage();
    }
    Serial.print("ID "); Serial.println(id);
    data = -1;
    Serial.println("aynı parmak tekrar girilmeli");
    while (data != FINGERPRINT_OK) {
        data = finger.getImage();
        switch (data) {
        case FINGERPRINT_OK:
        Serial.println("resim alındı");
        break;
        case FINGERPRINT_NOFINGER:
        Serial.print(".");
        break;
        case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println("iletişim hatası");
        break;
        case FINGERPRINT_IMAGEFAIL:
        Serial.println("hata");
        break;
        default:
        Serial.println("hata");
        break;
        }
    }

    // OK success!

    data = finger.image2Tz(2);
    switch (data) {
        case FINGERPRINT_OK:
        Serial.println("resim dönüştürüldü");
        break;
        case FINGERPRINT_IMAGEMESS:
        Serial.println("resim meşgul");
        return;
        case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println("bağlantı hatası");
        return;
        case FINGERPRINT_FEATUREFAIL:
        Serial.println("parmak izi özellikleri eşleşmedi");
        return;
        case FINGERPRINT_INVALIDIMAGE:
        Serial.println("parmak izi özellikleri eşleşmedi");
        return;
        default:
        Serial.println("hata");
        return;
    }

    Serial.print("Model Oluşturuldu #");  Serial.println(id);

    data = finger.createModel();
    if (data == FINGERPRINT_OK) {
        Serial.println("Parmak izleri eşleşti!");
    } else if (data == FINGERPRINT_PACKETRECIEVEERR) {
        Serial.println("Bağlantı hatası");
        return;
    } else if (data == FINGERPRINT_ENROLLMISMATCH) {
        Serial.println("Farklı parmak izleri");
        return;
    } else {
        Serial.println("hata");
        return;
    }

    Serial.print("ID "); Serial.println(id);
    
    data = finger.storeModel(id);
    
    if (data == FINGERPRINT_OK) {
        Serial.println("Hafızaya alındı");
    } else if (data == FINGERPRINT_PACKETRECIEVEERR) {
        Serial.println("Communication error");
        return;
    } else if (data == FINGERPRINT_BADLOCATION) {
        Serial.println("Bu bölümde bir boşluk iz bulunamadı");
        return;
    } else if (data == FINGERPRINT_FLASHERR) {
        Serial.println("Belleğe yazma hatası");
        return;
    } else {
        Serial.println("Unknown error");
        return;
    }
    return;
    
}


uint16_t fProcess::logIn() {


    Adafruit_Fingerprint finger = Adafruit_Fingerprint(&Serial2);
    finger.begin(57600);

    uint8_t data;
    while (data != FINGERPRINT_OK) {
    data = finger.getImage();
        switch (data) {
        case FINGERPRINT_OK:
        Serial.println("Parmak izi alındı ");
        break;
        case FINGERPRINT_NOFINGER:
        Serial.print(".");
        break;
        case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println("Bağlantı hatası");
        break;
        case FINGERPRINT_IMAGEFAIL:
        Serial.println("Hatalı resim");
        break;
        default:
        Serial.println("Bir hata meydana geldi");
        break;
        }
    }

    data = finger.image2Tz();
    switch (data) {
        case FINGERPRINT_OK:
        Serial.println("Resim dönüştürüldü");
        break;
        case FINGERPRINT_IMAGEMESS:
        Serial.println("resim bozuk");
        return FINGERPRINT_NOTFOUND;
        case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println("Bağlantı hatası");
        return FINGERPRINT_NOTFOUND;
        case FINGERPRINT_FEATUREFAIL:
        Serial.println("Could not find fingerprint features");
        return FINGERPRINT_NOTFOUND;
        case FINGERPRINT_INVALIDIMAGE:
        Serial.println("Could not find fingerprint features");
        return FINGERPRINT_NOTFOUND;
        default:
        Serial.println("Unknown error");
        return FINGERPRINT_NOTFOUND;
    }

    data = finger.fingerSearch();
    if (data == FINGERPRINT_OK) {
        Serial.println("Parmak izi eşleşti");
    } else if (data == FINGERPRINT_PACKETRECIEVEERR) {
        Serial.println("Bağlantı hatası");
        return FINGERPRINT_NOTFOUND;
    } else if (data == FINGERPRINT_NOTFOUND) {
        Serial.println("Did not find a match");
        return FINGERPRINT_NOTFOUND;
    } else {
        Serial.println("Unknown error");
        return FINGERPRINT_NOTFOUND;
    }

    Serial.print("Found ID #"); Serial.print(finger.fingerID);
    Serial.print(" with confidence of "); Serial.println(finger.confidence);

    return finger.fingerID;

}

void fProcess::showUserList() {

}