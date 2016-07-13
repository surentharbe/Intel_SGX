#include "HardningEndpoint_t.h"

#include "sgx_trts.h" /* for sgx_ocalloc, sgx_is_outside_enclave */

#include <string.h> /* for memcpy etc */
#include <stdlib.h> /* for malloc/free etc */

#define CHECK_REF_POINTER(ptr, siz) do {	\
	if (!(ptr) || ! sgx_is_outside_enclave((ptr), (siz)))	\
		return SGX_ERROR_INVALID_PARAMETER;\
} while (0)

#define CHECK_UNIQUE_POINTER(ptr, siz) do {	\
	if ((ptr) && ! sgx_is_outside_enclave((ptr), (siz)))	\
		return SGX_ERROR_INVALID_PARAMETER;\
} while (0)

/* sgx_ocfree() just restores the original outside stack pointer. */
#define OCALLOC(val, type, len) do {	\
	void* __tmp = sgx_ocalloc(len);	\
	if (__tmp == NULL) {	\
		sgx_ocfree();	\
		return SGX_ERROR_UNEXPECTED;\
	}			\
	(val) = (type)__tmp;	\
} while (0)


typedef struct ms_Encryption_t {
	char* ms_uData;
} ms_Encryption_t;

typedef struct ms_Decryption_t {
	char* ms_euData;
} ms_Decryption_t;

typedef struct ms_SecretInfo_t {
	char* ms_buf;
	size_t ms_len;
} ms_SecretInfo_t;

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4127)
#pragma warning(disable: 4200)
#endif

static sgx_status_t SGX_CDECL sgx_Encryption(void* pms)
{
	ms_Encryption_t* ms = SGX_CAST(ms_Encryption_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	char* _tmp_uData = ms->ms_uData;
	size_t _len_uData = _tmp_uData ? strlen(_tmp_uData) + 1 : 0;
	char* _in_uData = NULL;

	CHECK_REF_POINTER(pms, sizeof(ms_Encryption_t));
	CHECK_UNIQUE_POINTER(_tmp_uData, _len_uData);

	if (_tmp_uData != NULL) {
		_in_uData = (char*)malloc(_len_uData);
		if (_in_uData == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memcpy(_in_uData, _tmp_uData, _len_uData);
		_in_uData[_len_uData - 1] = '\0';
	}
	Encryption(_in_uData);
err:
	if (_in_uData) {
		memcpy(_tmp_uData, _in_uData, _len_uData);
		free(_in_uData);
	}

	return status;
}

static sgx_status_t SGX_CDECL sgx_Decryption(void* pms)
{
	ms_Decryption_t* ms = SGX_CAST(ms_Decryption_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	char* _tmp_euData = ms->ms_euData;
	size_t _len_euData = _tmp_euData ? strlen(_tmp_euData) + 1 : 0;
	char* _in_euData = NULL;

	CHECK_REF_POINTER(pms, sizeof(ms_Decryption_t));
	CHECK_UNIQUE_POINTER(_tmp_euData, _len_euData);

	if (_tmp_euData != NULL) {
		_in_euData = (char*)malloc(_len_euData);
		if (_in_euData == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memcpy(_in_euData, _tmp_euData, _len_euData);
		_in_euData[_len_euData - 1] = '\0';
	}
	Decryption(_in_euData);
err:
	if (_in_euData) {
		memcpy(_tmp_euData, _in_euData, _len_euData);
		free(_in_euData);
	}

	return status;
}

static sgx_status_t SGX_CDECL sgx_SecretInfo(void* pms)
{
	ms_SecretInfo_t* ms = SGX_CAST(ms_SecretInfo_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	char* _tmp_buf = ms->ms_buf;
	size_t _tmp_len = ms->ms_len;
	size_t _len_buf = _tmp_len;
	char* _in_buf = NULL;

	CHECK_REF_POINTER(pms, sizeof(ms_SecretInfo_t));
	CHECK_UNIQUE_POINTER(_tmp_buf, _len_buf);

	if (_tmp_buf != NULL) {
		if ((_in_buf = (char*)malloc(_len_buf)) == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memset((void*)_in_buf, 0, _len_buf);
	}
	SecretInfo(_in_buf, _tmp_len);
err:
	if (_in_buf) {
		memcpy(_tmp_buf, _in_buf, _len_buf);
		free(_in_buf);
	}

	return status;
}

SGX_EXTERNC const struct {
	size_t nr_ecall;
	struct {void* call_addr; uint8_t is_priv;} ecall_table[3];
} g_ecall_table = {
	3,
	{
		{(void*)(uintptr_t)sgx_Encryption, 0},
		{(void*)(uintptr_t)sgx_Decryption, 0},
		{(void*)(uintptr_t)sgx_SecretInfo, 0},
	}
};

SGX_EXTERNC const struct {
	size_t nr_ocall;
} g_dyn_entry_table = {
	0,
};


#ifdef _MSC_VER
#pragma warning(pop)
#endif
