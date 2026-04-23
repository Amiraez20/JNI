#include <jni.h>
#include <string>
#include <algorithm>
#include <climits>
#include <android/log.h>

#define MODULE_TAG "NATIVECALC"
#define LOG_INFO(...) __android_log_print(ANDROID_LOG_INFO, MODULE_TAG, __VA_ARGS__)
#define LOG_ERR(...) __android_log_print(ANDROID_LOG_ERROR, MODULE_TAG, __VA_ARGS__)

extern "C"
JNIEXPORT jstring JNICALL
Java_com_lab_nativecalc_ComputeActivity_computeGreeting(
        JNIEnv* ctx,
        jobject) {

    LOG_INFO("computeGreeting invoque depuis la couche native");
    return ctx->NewStringUTF("Bonjour depuis le moteur C++ natif !");
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_lab_nativecalc_ComputeActivity_computeFactorial(
        JNIEnv* ctx,
        jobject,
        jint inputVal) {

    if (inputVal < 0) {
        LOG_ERR("Valeur negative refusee");
        return -1;
    }

    long long result = 1;
    for (int step = 1; step <= inputVal; step++) {
        result *= step;
        if (result > INT_MAX) {
            LOG_ERR("Debordement detecte pour inputVal=%d", inputVal);
            return -2;
        }
    }

    LOG_INFO("Factoriel de %d = %lld", inputVal, result);
    return static_cast<jint>(result);
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_lab_nativecalc_ComputeActivity_invertText(
        JNIEnv* ctx,
        jobject,
        jstring inputText) {

    if (inputText == nullptr) {
        LOG_ERR("Texte nul transmis");
        return ctx->NewStringUTF("Erreur : texte absent");
    }

    const char* rawBytes = ctx->GetStringUTFChars(inputText, nullptr);
    if (rawBytes == nullptr) {
        LOG_ERR("Lecture du texte Java impossible");
        return ctx->NewStringUTF("Erreur de lecture JNI");
    }

    std::string buffer(rawBytes);
    ctx->ReleaseStringUTFChars(inputText, rawBytes);

    std::reverse(buffer.begin(), buffer.end());

    LOG_INFO("Texte inverse : %s", buffer.c_str());
    return ctx->NewStringUTF(buffer.c_str());
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_lab_nativecalc_ComputeActivity_totalizeArray(
        JNIEnv* ctx,
        jobject,
        jintArray inputData) {

    if (inputData == nullptr) {
        LOG_ERR("Tableau de donnees nul");
        return -1;
    }

    jsize dataLength = ctx->GetArrayLength(inputData);
    jint* dataPtr = ctx->GetIntArrayElements(inputData, nullptr);

    if (dataPtr == nullptr) {
        LOG_ERR("Acces aux elements du tableau impossible");
        return -2;
    }

    long long accumulator = 0;
    for (jsize idx = 0; idx < dataLength; idx++) {
        accumulator += dataPtr[idx];
    }

    ctx->ReleaseIntArrayElements(inputData, dataPtr, 0);

    if (accumulator > INT_MAX) {
        LOG_ERR("Debordement sur l'accumulateur");
        return -3;
    }

    LOG_INFO("Somme totale = %lld", accumulator);
    return static_cast<jint>(accumulator);
}