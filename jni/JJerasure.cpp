#include <stdlib.h>

#include "JJerasure.h"
#include "jerasure.h"
#include "javautility.h"
#include "reed_sol.h"

#define talloc(type, num) (type *) malloc(sizeof(type)*(num))

/*
 * Class:     cn_ctyun_ec_jni_Jerasure
 * Method:    jerasure_matrix_to_bitmatrix
 * Signature: (III[I)[I
 */
JNIEXPORT jintArray JNICALL Java_cn_ctyun_ec_jni_Jerasure_jerasure_1matrix_1to_1bitmatrix
  (JNIEnv *env, jclass clazz, jint k, jint m, jint w, jintArray jmatrix)
{
	bool outOfMemory = false;
	jintArray result = NULL;

	jint* matrix = env->GetIntArrayElements(jmatrix, NULL);
	if(matrix != NULL) {
		int* resultMatrix = jerasure_matrix_to_bitmatrix(k, m, w, (int*)matrix);

		if(resultMatrix != NULL) {
			result = env->NewIntArray(k*m*w*w);

			if(result != NULL) {
				env->SetIntArrayRegion(result, 0, k*m*w*w, (jint*)resultMatrix);
			} else {
				outOfMemory = true;
			}
		} else {
			outOfMemory = true;
		}

		free(resultMatrix);
	} else {
		outOfMemory = true;
	}

	if(outOfMemory) {
		throwOutOfMemoryError(env, "Could not allocate memory.");
	}

	env->ReleaseIntArrayElements(jmatrix, matrix, NULL);

	return result;
}

/*
 * Class:     cn_ctyun_ec_jni_Jerasure
 * Method:    jerasure_do_parity
 * Signature: (I[Ljava/nio/ByteBuffer;Ljava/nio/ByteBuffer;I)V
 */
JNIEXPORT void JNICALL Java_cn_ctyun_ec_jni_Jerasure_jerasure_1do_1parity
  (JNIEnv *env, jclass clazz, jint k, jobjectArray jdata_ptrs, jobject jparity_ptr, jint size)
{
	char **data = convertFromBufferArray(env, jdata_ptrs);
	char *coding = (char*)env->GetDirectBufferAddress(jparity_ptr);
	jerasure_do_parity(k, data, coding, size);
	delete[] data;
}

/*
 * Class:     cn_ctyun_ec_jni_Jerasure
 * Method:    jerasure_matrix_encode
 * Signature: (III[I[Ljava/nio/ByteBuffer;[Ljava/nio/ByteBuffer;I)V
 */
JNIEXPORT void JNICALL Java_cn_ctyun_ec_jni_Jerasure_jerasure_1matrix_1encode
	(JNIEnv *env, jclass clazz, jint k, jint m, jint w, jintArray jmatrix, jobjectArray jdata_ptrs, jobjectArray jcoding_ptrs, jint size)
{
	jint* matrix = env->GetIntArrayElements(jmatrix, NULL);
	if(matrix == NULL){
		throwOutOfMemoryError(env, "");
	}
	
	char **data = convertFromBufferArray(env, jdata_ptrs);
	char **coding = convertFromBufferArray(env, jcoding_ptrs);
	jerasure_matrix_encode(k, m ,w, (int*)matrix, data, coding, size);

	env->ReleaseIntArrayElements(jmatrix, matrix, NULL);
	delete[] data;
	delete[] coding;
}

/*
 * Class:     cn_ctyun_ec_jni_Jerasure
 * Method:    jerasure_bitmatrix_encode
 * Signature: (III[I[Ljava/nio/ByteBuffer;[Ljava/nio/ByteBuffer;II)V
 */
JNIEXPORT void JNICALL Java_cn_ctyun_ec_jni_Jerasure_jerasure_1bitmatrix_1encode
  (JNIEnv *env, jclass clazz, jint k, jint m, jint w, jintArray jbitmatrix, jobjectArray jdata_ptrs, jobjectArray jcoding_ptrs, jint size, jint packetsize)
{
	jint* bitmatrix = env->GetIntArrayElements(jbitmatrix, NULL);
	if(bitmatrix == NULL){
		throwOutOfMemoryError(env, "");
	}

	char **data = convertFromBufferArray(env, jdata_ptrs);
	char **coding = convertFromBufferArray(env, jcoding_ptrs);
	jerasure_bitmatrix_encode(k,m,w, (int*)bitmatrix, data, coding, size, packetsize);

	env->ReleaseIntArrayElements(jbitmatrix, bitmatrix, NULL);
	delete[] data;
	delete[] coding;
}

/*
 * Class:     cn_ctyun_ec_jni_Jerasure
 * Method:    jerasure_matrix_decode
 * Signature: (III[IZ[I[Ljava/nio/ByteBuffer;[Ljava/nio/ByteBuffer;I)Z
 */
JNIEXPORT jboolean JNICALL Java_cn_ctyun_ec_jni_Jerasure_jerasure_1matrix_1decode
  (JNIEnv *env, jclass clazz, jint k, jint m, jint w, jintArray jmatrix, jboolean row_k_ones, jintArray jerasures, jobjectArray jdata_ptrs, jobjectArray jcoding_ptrs, jint size)
{
	int result = -1;
	jint *erasures = NULL, *matrix = NULL;

	erasures = env->GetIntArrayElements(jerasures, NULL);
	matrix = env->GetIntArrayElements(jmatrix, NULL);
	char **data = convertFromBufferArray(env, jdata_ptrs);
	char **coding = convertFromBufferArray(env, jcoding_ptrs);

	if(erasures != NULL && matrix != NULL){
		result = jerasure_matrix_decode(k, m, w, (int*)matrix, (row_k_ones == JNI_TRUE ? 1 : 0), (int*)erasures, data, coding, size);
	} else {
		throwOutOfMemoryError(env, "");
	}

	env->ReleaseIntArrayElements(jmatrix, matrix, NULL);
	env->ReleaseIntArrayElements(jerasures, erasures, NULL);
	delete[] data;
	delete[] coding;

	if(result == 0)
		return JNI_TRUE;

	return JNI_FALSE;
}

/*
 * Class:     cn_ctyun_ec_jni_Jerasure
 * Method:    jerasure_bitmatrix_decode
 * Signature: (III[IZ[I[Ljava/nio/ByteBuffer;[Ljava/nio/ByteBuffer;II)Z
 */
JNIEXPORT jboolean JNICALL Java_cn_ctyun_ec_jni_Jerasure_jerasure_1bitmatrix_1decode
  (JNIEnv *env, jclass clazz, jint k, jint m, jint w, jintArray jbitmatrix, jboolean row_k_ones, jintArray jerasures, jobjectArray jdata_ptrs, jobjectArray jcoding_ptrs, jint size, jint packetsize)
{
	int result = -1;
	jint *bitmatrix = NULL, *erasures = NULL;

	bitmatrix = env->GetIntArrayElements(jbitmatrix, NULL);
	erasures = env->GetIntArrayElements(jerasures, NULL);
	char **data = convertFromBufferArray(env, jdata_ptrs);
	char **coding = convertFromBufferArray(env, jcoding_ptrs);

	if(bitmatrix != NULL && erasures != NULL) {
		result = jerasure_bitmatrix_decode(k,m,w, (int*)bitmatrix, (row_k_ones == JNI_TRUE ? 1 : 0), (int*)erasures, data, coding, size, packetsize);
	} else {
		throwOutOfMemoryError(env, "");
	}

	env->ReleaseIntArrayElements(jbitmatrix, bitmatrix, NULL);
	env->ReleaseIntArrayElements(jerasures, erasures, NULL);
	delete[] data;
	delete[] coding;

	if(result == 0)
		return JNI_TRUE;

	return JNI_FALSE;
}

/*
 * Class:     cn_ctyun_ec_jni_Jerasure
 * Method:    jerasure_make_decoding_matrix
 * Signature: (III[I[Z[I[I)Z
 */
JNIEXPORT jboolean JNICALL Java_cn_ctyun_ec_jni_Jerasure_jerasure_1make_1decoding_1matrix
  (JNIEnv *env, jclass clazz, jint k, jint m, jint w, jintArray jmatrix, jbooleanArray jerased, jintArray jdecoding_matrix, jintArray jdm_ids)
{
	int result = -1;
	int *erased = talloc(int, k+m);
	jboolean* erasedj = env->GetBooleanArrayElements(jerased, NULL);
	jint* matrix = env->GetIntArrayElements(jmatrix, NULL);
	jint* decoding_matrix = env->GetIntArrayElements(jdecoding_matrix, NULL);
	jint* dm_ids = env->GetIntArrayElements(jdm_ids, NULL);

	if(matrix != NULL && erased != NULL && erasedj != NULL && matrix != NULL && decoding_matrix != NULL && dm_ids != NULL) {
		for(int i = 0; i < (k+m); ++i) {
			if(erasedj[i] == JNI_TRUE) {
				erased[i] = 1;
			} else {
				erased[i] = 0;
			}
		}

		result = jerasure_make_decoding_matrix(k, m, w, (int*)matrix, erased, (int*)decoding_matrix, (int*)dm_ids);
	} else {
		throwOutOfMemoryError(env, "");
	}

	env->ReleaseBooleanArrayElements(jerased, erasedj, NULL);
	env->ReleaseIntArrayElements(jmatrix, matrix, NULL);
	env->ReleaseIntArrayElements(jdecoding_matrix, decoding_matrix, NULL);
	env->ReleaseIntArrayElements(jdm_ids, dm_ids, NULL);

	free(erased);

	if(result == 0)
		return JNI_TRUE;

	return JNI_FALSE;
}

/*
 * Class:     cn_ctyun_ec_jni_Jerasure
 * Method:    jerasure_make_decoding_bitmatrix
 * Signature: (III[I[Z[I[I)Z
 */
JNIEXPORT jboolean JNICALL Java_cn_ctyun_ec_jni_Jerasure_jerasure_1make_1decoding_1bitmatrix
	(JNIEnv *env, jclass clazz, jint k, jint m, jint w, jintArray jmatrix, jbooleanArray jerased, jintArray jdecoding_matrix, jintArray jdm_ids)
{
	int result = -1;
	int* erased = talloc(int, k+m);
	jboolean* erasedj = env->GetBooleanArrayElements(jerased, NULL);
	jint* dm_ids = env->GetIntArrayElements(jdm_ids, NULL);
	jint* decoding_matrix = env->GetIntArrayElements(jdecoding_matrix, NULL);
	jint* matrix = env->GetIntArrayElements(jmatrix, NULL);

	if(erasedj != NULL && erased != NULL && dm_ids != NULL && decoding_matrix != NULL && matrix != NULL) {
		for(int i = 0; i < k+m; ++i) {
			if(erasedj[i] == JNI_TRUE) {
				erased[i] = 1;
			} else {
				erased[i] = 0;
			}
		}

		result = jerasure_make_decoding_bitmatrix(k, m, w, (int*)matrix, erased, (int*)decoding_matrix, (int*)dm_ids);

	} else {
		throwOutOfMemoryError(env, "");
	}

	free(erased);
	env->ReleaseBooleanArrayElements(jerased, erasedj, NULL);
	env->ReleaseIntArrayElements(jdm_ids, dm_ids, NULL);
	env->ReleaseIntArrayElements(jdecoding_matrix, decoding_matrix, NULL);
	env->ReleaseIntArrayElements(jmatrix, matrix, NULL);

	if(result == 0)
		return JNI_TRUE;

	return JNI_FALSE;
}

/*
 * Class:     cn_ctyun_ec_jni_Jerasure
 * Method:    jerasure_erasures_to_erased
 * Signature: (II[I)[Z
 */
JNIEXPORT jbooleanArray JNICALL Java_cn_ctyun_ec_jni_Jerasure_jerasure_1erasures_1to_1erased
	(JNIEnv *env, jclass clazz, jint k, jint m, jintArray jerasures)
{
	bool outOfMemory = false;
	jbooleanArray result;

	jint* erasures = env->GetIntArrayElements(jerasures, NULL);

	if(erasures != NULL) {
		int *erased = jerasure_erasures_to_erased(k,m,(int*)erasures);
		if(erased != NULL)
		{
			result = env->NewBooleanArray(k+m);

			if(result != NULL) {
				jboolean* resultValues = env->GetBooleanArrayElements(result, NULL);

				for(int i = 0; i < k+m; ++i) {
					resultValues[i] = (erased[i] == 1 ? JNI_TRUE : JNI_FALSE);
				}

				env->ReleaseBooleanArrayElements(result, resultValues, NULL);
			} else {
				outOfMemory = true;
			}
		} else {
			outOfMemory = true;
		}

		free(erased);
	} else {
		outOfMemory = true;
	}

	if(outOfMemory) {
		throwOutOfMemoryError(env, "");
	}

	env->ReleaseIntArrayElements(jerasures, erasures, NULL);

	return result;
}

/*
* Class:     cn_ctyun_ec_jni_Jerasure
* Method:    jerasure_matrix_dotprod
* Signature: (II[I[II[[B[[BI)V
*/
JNIEXPORT void JNICALL Java_cn_ctyun_ec_jni_Jerasure_jerasure_1matrix_1dotprod
	(JNIEnv *env, jclass clazz, jint, jint, jintArray, jintArray, jint, jobjectArray, jobjectArray, jint);

/*
* Class:     cn_ctyun_ec_jni_Jerasure
* Method:    jerasure_bitmatrix_dotprod
* Signature: (II[I[II[[B[[BII)V
*/
JNIEXPORT void JNICALL Java_cn_ctyun_ec_jni_Jerasure_jerasure_1bitmatrix_1dotprod
	(JNIEnv *env, jclass clazz, jint, jint, jintArray, jintArray, jint, jobjectArray, jobjectArray, jint, jint);

/*
* Class:     cn_ctyun_ec_jni_Jerasure
* Method:    jerasure_invert_matrix
* Signature: ([I[III)I
*/
JNIEXPORT jint JNICALL Java_cn_ctyun_ec_jni_Jerasure_jerasure_1invert_1matrix
	(JNIEnv *env, jclass clazz, jintArray, jintArray, jint, jint);

/*
* Class:     cn_ctyun_ec_jni_Jerasure
* Method:    jerasure_invert_bitmatrix
* Signature: ([I[II)I
*/
JNIEXPORT jint JNICALL Java_cn_ctyun_ec_jni_Jerasure_jerasure_1invert_1bitmatrix
	(JNIEnv *env, jclass clazz, jintArray, jintArray, jint);

/*
* Class:     cn_ctyun_ec_jni_Jerasure
* Method:    jerasure_invertible_matrix
* Signature: ([III)I
*/
JNIEXPORT jint JNICALL Java_cn_ctyun_ec_jni_Jerasure_jerasure_1invertible_1matrix
	(JNIEnv *env, jclass clazz, jintArray, jint, jint);

/*
* Class:     cn_ctyun_ec_jni_Jerasure
* Method:    jerasure_invertible_bitmatrix
* Signature: ([II)I
*/
JNIEXPORT jint JNICALL Java_cn_ctyun_ec_jni_Jerasure_jerasure_1invertible_1bitmatrix
	(JNIEnv *env, jclass clazz, jintArray, jint);

/*
* Class:     cn_ctyun_ec_jni_Jerasure
* Method:    jerasure_print_matrix
* Signature: ([IIII)V
*/
JNIEXPORT void JNICALL Java_cn_ctyun_ec_jni_Jerasure_jerasure_1print_1matrix
	(JNIEnv *env, jclass clazz, jintArray, jint, jint, jint);

/*
* Class:     cn_ctyun_ec_jni_Jerasure
* Method:    jerasure_print_bitmatrix
* Signature: ([IIII)V
*/
JNIEXPORT void JNICALL Java_cn_ctyun_ec_jni_Jerasure_jerasure_1print_1bitmatrix
	(JNIEnv *env, jclass clazz, jintArray, jint, jint, jint);

/*
* Class:     cn_ctyun_ec_jni_Jerasure
* Method:    jerasure_matrix_multiply
* Signature: ([I[IIIIII)[I
*/
JNIEXPORT jintArray JNICALL Java_cn_ctyun_ec_jni_Jerasure_jerasure_1matrix_1multiply
	(JNIEnv *env, jclass clazz, jintArray, jintArray, jint, jint, jint, jint, jint);

/*
* Class:     cn_ctyun_ec_jni_Jerasure
* Method:    jerasure_get_stats
* Signature: ([D)V
*/
JNIEXPORT void JNICALL Java_cn_ctyun_ec_jni_Jerasure_jerasure_1get_1stats
	(JNIEnv *env, jclass clazz, jdoubleArray);

/*
 * Class:     cn_ctyun_ec_jni_Jerasure
 * Method:    my_jerasure_matrix_encode
 * Signature: (IIIJ[Ljava/nio/ByteBuffer;[Ljava/nio/ByteBuffer;I)V
 */
JNIEXPORT void JNICALL Java_cn_ctyun_ec_jni_Jerasure_my_1jerasure_1matrix_1encode
  (JNIEnv *env, jclass clazz, jint k, jint m, jint w, jlong jmatrixId, jobjectArray jdata_ptrs, jobjectArray jcoding_ptrs, jint size)
  {
	int* matrix = (int*) jmatrixId;
	char **data = convertFromBufferArray(env, jdata_ptrs);
	char **coding = convertFromBufferArray(env, jcoding_ptrs);
	jerasure_matrix_encode(k, m ,w, (int*)matrix, data, coding, size);

	delete[] data;
	delete[] coding;
}


/*
 * Class:     cn_ctyun_ec_jni_Jerasure
 * Method:    my_jerasure_matrix_decode
 * Signature: (IIIJZ[I[Ljava/nio/ByteBuffer;[Ljava/nio/ByteBuffer;I)Z
 */
JNIEXPORT jboolean JNICALL Java_cn_ctyun_ec_jni_Jerasure_my_1jerasure_1matrix_1decode
  (JNIEnv *env, jclass clazz, jint k, jint m, jint w, jlong jmatrixId, jboolean row_k_ones, jintArray jerasures, jobjectArray jdata_ptrs, jobjectArray jcoding_ptrs, jint size)
  {
	int result = -1;
	jint *erasures = NULL;

	erasures = env->GetIntArrayElements(jerasures, NULL);
	int *matrix = (int*) jmatrixId;
	char **data = convertFromBufferArray(env, jdata_ptrs);
	char **coding = convertFromBufferArray(env, jcoding_ptrs);

	if(erasures != NULL && matrix != NULL){
		result = jerasure_matrix_decode(k, m, w, (int*)matrix, (row_k_ones == JNI_TRUE ? 1 : 0), (int*)erasures, data, coding, size);
	} else {
		throwOutOfMemoryError(env, "");
	}

	env->ReleaseIntArrayElements(jerasures, erasures, NULL);
	delete[] data;
	delete[] coding;

	if(result == 0)
		return JNI_TRUE;

	return JNI_FALSE;
}