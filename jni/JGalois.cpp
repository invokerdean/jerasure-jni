#include "javautility.h"
#include "JGalois.h"
#include "galois.h"

/*
 * Class:     cn_ctyun_ec_jni_Galois
 * Method:    galois_single_multiply
 * Signature: (III)I
 */
JNIEXPORT jint JNICALL Java_cn_ctyun_ec_jni_Galois_galois_1single_1multiply
	(JNIEnv *env, jclass clazz, jint a, jint b, jint w)
{
	return galois_single_multiply(a, b, w);
}

/*
 * Class:     cn_ctyun_ec_jni_Galois
 * Method:    galois_single_divide
 * Signature: (III)I
 */
JNIEXPORT jint JNICALL Java_cn_ctyun_ec_jni_Galois_galois_1single_1divide
	(JNIEnv *env, jclass clazz, jint a, jint b, jint w)
{
	return galois_single_divide(a, b, w);
}

/*
 * Class:     cn_ctyun_ec_jni_Galois
 * Method:    galois_log
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_cn_ctyun_ec_jni_Galois_galois_1log
	(JNIEnv *env, jclass clazz, jint value, jint w)
{
	return galois_log(value, w);
}

/*
 * Class:     cn_ctyun_ec_jni_Galois
 * Method:    galois_ilog
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_cn_ctyun_ec_jni_Galois_galois_1ilog
	(JNIEnv *env, jclass clazz, jint value, jint w)
{
	return galois_ilog(value, w);
}

/*
 * Class:     cn_ctyun_ec_jni_Galois
 * Method:    galois_create_log_tables
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_cn_ctyun_ec_jni_Galois_galois_1create_1log_1tables
	(JNIEnv *env, jclass clazz, jint w)
{
	int result = galois_create_log_tables(w);

	return (result == 0 ? JNI_TRUE : JNI_FALSE);
}

/*
 * Class:     cn_ctyun_ec_jni_Galois
 * Method:    galois_logtable_multiply
 * Signature: (III)I
 */
JNIEXPORT jint JNICALL Java_cn_ctyun_ec_jni_Galois_galois_1logtable_1multiply
	(JNIEnv *env, jclass clazz, jint x, jint y, jint w)
{
	return galois_logtable_multiply(x, y, w);
}

/*
 * Class:     cn_ctyun_ec_jni_Galois
 * Method:    galois_logtable_divide
 * Signature: (III)I
 */
JNIEXPORT jint JNICALL Java_cn_ctyun_ec_jni_Galois_galois_1logtable_1divide
	(JNIEnv *env, jclass clazz, jint x, jint y, jint w)
{
	return galois_logtable_divide(x, y, w);
}

/*
 * Class:     cn_ctyun_ec_jni_Galois
 * Method:    galois_create_mult_tables
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_cn_ctyun_ec_jni_Galois_galois_1create_1mult_1tables
	(JNIEnv *env, jclass clazz, jint w)
{
	int result = galois_create_mult_tables(w);

	return (result == 0 ? JNI_TRUE : JNI_FALSE);
}

/*
 * Class:     cn_ctyun_ec_jni_Galois
 * Method:    galois_multtable_multiply
 * Signature: (III)I
 */
JNIEXPORT jint JNICALL Java_cn_ctyun_ec_jni_Galois_galois_1multtable_1multiply
	(JNIEnv *env, jclass clazz, jint x, jint y, jint w)
{
	return galois_multtable_multiply(x, y, w);
}

/*
 * Class:     cn_ctyun_ec_jni_Galois
 * Method:    galois_multtable_divide
 * Signature: (III)I
 */
JNIEXPORT jint JNICALL Java_cn_ctyun_ec_jni_Galois_galois_1multtable_1divide
	(JNIEnv *env, jclass clazz, jint x, jint y, jint w)
{
	return galois_multtable_divide(x, y, w);
}

/*
 * Class:     cn_ctyun_ec_jni_Galois
 * Method:    galois_shift_multiply
 * Signature: (III)I
 */
JNIEXPORT jint JNICALL Java_cn_ctyun_ec_jni_Galois_galois_1shift_1multiply
	(JNIEnv *env, jclass clazz, jint x, jint y, jint w)
{
	return galois_shift_multiply(x, y, w);
}

/*
 * Class:     cn_ctyun_ec_jni_Galois
 * Method:    galois_shift_divide
 * Signature: (III)I
 */
JNIEXPORT jint JNICALL Java_cn_ctyun_ec_jni_Galois_galois_1shift_1divide
	(JNIEnv *env, jclass clazz, jint x, jint y, jint w)
{
	return galois_shift_divide(x, y, w);
}

/*
 * Class:     cn_ctyun_ec_jni_Galois
 * Method:    galois_create_split_w8_tables
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_cn_ctyun_ec_jni_Galois_galois_1create_1split_1w8_1tables
	(JNIEnv *env, jclass clazz)
{
	return galois_create_split_w8_tables() == 0 ? JNI_TRUE : JNI_FALSE;
}

/*
 * Class:     cn_ctyun_ec_jni_Galois
 * Method:    galois_split_w8_multiply
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_cn_ctyun_ec_jni_Galois_galois_1split_1w8_1multiply
	(JNIEnv *env, jclass clazz, jint x, jint y)
{
	return galois_split_w8_multiply(x, y);
}

/*
 * Class:     cn_ctyun_ec_jni_Galois
 * Method:    galois_inverse
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_cn_ctyun_ec_jni_Galois_galois_1inverse
	(JNIEnv *env, jclass clazz, jint x, jint w)
{
	return galois_inverse(x, w);
}

/*
 * Class:     cn_ctyun_ec_jni_Galois
 * Method:    galois_shift_inverse
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_cn_ctyun_ec_jni_Galois_galois_1shift_1inverse
	(JNIEnv *env, jclass clazz, jint y, jint w)
{
	return galois_shift_inverse(y, w);
}

/*
 * Class:     cn_ctyun_ec_jni_Galois
 * Method:    galois_region_xor
 * Signature: (Ljava/nio/ByteBuffer;Ljava/nio/ByteBuffer;Ljava/nio/ByteBuffer;I)V
 */
JNIEXPORT void JNICALL Java_cn_ctyun_ec_jni_Galois_galois_1region_1xor
  (JNIEnv *env, jclass clazz, jobject jr1, jobject jr2, jobject jr3, jint nbytes)
{
	char *r1 = (char*)env->GetDirectBufferAddress(jr1);
	char *r2 = (char*)env->GetDirectBufferAddress(jr2);
	char *r3 = (char*)env->GetDirectBufferAddress(jr3);

	if(!(r1 == NULL || r2 == NULL || r3 == NULL)) {
		galois_region_xor((char*)r1, (char*)r2, (char*)r3, nbytes);
	}
}

/*
 * Class:     cn_ctyun_ec_jni_Galois
 * Method:    galois_w08_region_multiply
 * Signature: (Ljava/nio/ByteBuffer;IILjava/nio/ByteBuffer;Z)V
 */
JNIEXPORT void JNICALL Java_cn_ctyun_ec_jni_Galois_galois_1w08_1region_1multiply
  (JNIEnv *env, jclass clazz, jobject jregion, jint multby, jint nbytes, jobject jr2, jboolean add)
{
	char *region = (char *)env->GetDirectBufferAddress(jregion);
	if(region == NULL) {
		throwOutOfMemoryError(env, "Error getting region from Java");
		return;
	}

	char *r2 = NULL;
	if(jr2 != NULL)
	{
		r2 = (char *) env->GetDirectBufferAddress(jr2);
		if(r2 == NULL) {
			throwOutOfMemoryError(env, "Error getting r2 from Java");
			return;
		}
	}

	galois_w08_region_multiply((char*)region, multby, nbytes, (char*)r2, (add == JNI_TRUE ? 1 : 0));
}

/*
 * Class:     cn_ctyun_ec_jni_Galois
 * Method:    galois_w16_region_multiply
 * Signature: (Ljava/nio/ByteBuffer;IILjava/nio/ByteBuffer;Z)V
 */
JNIEXPORT void JNICALL Java_cn_ctyun_ec_jni_Galois_galois_1w16_1region_1multiply
  (JNIEnv *env, jclass clazz, jobject jregion, jint multby, jint nbytes, jobject jr2, jboolean add)
{
	char *region = (char *)env->GetDirectBufferAddress(jregion);
	if(region == NULL) {
		throwOutOfMemoryError(env, "Error getting region from Java");
		return;
	}

	char* r2 = NULL;
	if(jr2 != NULL)
	{
		r2 = (char *) env->GetDirectBufferAddress(jr2);

		if(r2 == NULL) {
			throwOutOfMemoryError(env, "Error getting r2 from Java");
			return;
		}
	}

	galois_w16_region_multiply((char*)region, multby, nbytes, (char*)r2, (add == JNI_TRUE ? 1 : 0));
}

/*
 * Class:     cn_ctyun_ec_jni_Galois
 * Method:    galois_w32_region_multiply
 * Signature: (Ljava/nio/ByteBuffer;IILjava/nio/ByteBuffer;Z)V
 */
JNIEXPORT void JNICALL Java_cn_ctyun_ec_jni_Galois_galois_1w32_1region_1multiply
  (JNIEnv *env, jclass clazz, jobject jregion, jint multby, jint nbytes, jobject jr2, jboolean add)
{
	char *region = (char *)env->GetDirectBufferAddress(jregion);
	if(region == NULL) {
		throwOutOfMemoryError(env, "Error getting region from Java");
		return;
	}

	char *r2 = NULL;
	if(jr2 != NULL)
	{
		r2 = (char *) env->GetDirectBufferAddress(jr2);

		if(r2 == NULL) {
			throwOutOfMemoryError(env, "Error getting r2 from Java");
			return;
		}
	}

	galois_w32_region_multiply((char*)region, multby, nbytes, (char*)r2, (add == JNI_TRUE ? 1 : 0));
}