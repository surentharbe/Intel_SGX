#include "Enclave2_t.h"

#include "sgx_trts.h" /* for sgx_ocalloc, sgx_is_outside_enclave */

#include <errno.h>
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


typedef struct ms_enclaveChangeBuffer_t {
	char* ms_buf;
	size_t ms_len;
} ms_enclaveChangeBuffer_t;

typedef struct ms_enclaveStringSave_t {
	char* ms_input;
	size_t ms_len;
} ms_enclaveStringSave_t;

typedef struct ms_enclaveStringLoad_t {
	char* ms_output;
	size_t ms_len;
} ms_enclaveStringLoad_t;

typedef struct ms_enclaveSaveInt_t {
	int ms_input;
} ms_enclaveSaveInt_t;

typedef struct ms_enclaveLoadInt_t {
	int ms_retval;
} ms_enclaveLoadInt_t;

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4127)
#pragma warning(disable: 4200)
#endif

static sgx_status_t SGX_CDECL sgx_enclaveChangeBuffer(void* pms)
{
	ms_enclaveChangeBuffer_t* ms = SGX_CAST(ms_enclaveChangeBuffer_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	char* _tmp_buf = ms->ms_buf;
	size_t _tmp_len = ms->ms_len;
	size_t _len_buf = _tmp_len;
	char* _in_buf = NULL;

	CHECK_REF_POINTER(pms, sizeof(ms_enclaveChangeBuffer_t));
	CHECK_UNIQUE_POINTER(_tmp_buf, _len_buf);

	if (_tmp_buf != NULL) {
		if ((_in_buf = (char*)malloc(_len_buf)) == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memset((void*)_in_buf, 0, _len_buf);
	}
	enclaveChangeBuffer(_in_buf, _tmp_len);
err:
	if (_in_buf) {
		memcpy(_tmp_buf, _in_buf, _len_buf);
		free(_in_buf);
	}

	return status;
}

static sgx_status_t SGX_CDECL sgx_enclaveStringSave(void* pms)
{
	ms_enclaveStringSave_t* ms = SGX_CAST(ms_enclaveStringSave_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	char* _tmp_input = ms->ms_input;
	size_t _tmp_len = ms->ms_len;
	size_t _len_input = _tmp_len;
	char* _in_input = NULL;

	CHECK_REF_POINTER(pms, sizeof(ms_enclaveStringSave_t));
	CHECK_UNIQUE_POINTER(_tmp_input, _len_input);

	if (_tmp_input != NULL) {
		_in_input = (char*)malloc(_len_input);
		if (_in_input == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memcpy(_in_input, _tmp_input, _len_input);
	}
	enclaveStringSave(_in_input, _tmp_len);
err:
	if (_in_input) free(_in_input);

	return status;
}

static sgx_status_t SGX_CDECL sgx_enclaveStringLoad(void* pms)
{
	ms_enclaveStringLoad_t* ms = SGX_CAST(ms_enclaveStringLoad_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	char* _tmp_output = ms->ms_output;
	size_t _tmp_len = ms->ms_len;
	size_t _len_output = _tmp_len;
	char* _in_output = NULL;

	CHECK_REF_POINTER(pms, sizeof(ms_enclaveStringLoad_t));
	CHECK_UNIQUE_POINTER(_tmp_output, _len_output);

	if (_tmp_output != NULL) {
		if ((_in_output = (char*)malloc(_len_output)) == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memset((void*)_in_output, 0, _len_output);
	}
	enclaveStringLoad(_in_output, _tmp_len);
err:
	if (_in_output) {
		memcpy(_tmp_output, _in_output, _len_output);
		free(_in_output);
	}

	return status;
}

static sgx_status_t SGX_CDECL sgx_enclaveSaveInt(void* pms)
{
	ms_enclaveSaveInt_t* ms = SGX_CAST(ms_enclaveSaveInt_t*, pms);
	sgx_status_t status = SGX_SUCCESS;

	CHECK_REF_POINTER(pms, sizeof(ms_enclaveSaveInt_t));

	enclaveSaveInt(ms->ms_input);


	return status;
}

static sgx_status_t SGX_CDECL sgx_enclaveLoadInt(void* pms)
{
	ms_enclaveLoadInt_t* ms = SGX_CAST(ms_enclaveLoadInt_t*, pms);
	sgx_status_t status = SGX_SUCCESS;

	CHECK_REF_POINTER(pms, sizeof(ms_enclaveLoadInt_t));

	ms->ms_retval = enclaveLoadInt();


	return status;
}

SGX_EXTERNC const struct {
	size_t nr_ecall;
	struct {void* call_addr; uint8_t is_priv;} ecall_table[5];
} g_ecall_table = {
	5,
	{
		{(void*)(uintptr_t)sgx_enclaveChangeBuffer, 0},
		{(void*)(uintptr_t)sgx_enclaveStringSave, 0},
		{(void*)(uintptr_t)sgx_enclaveStringLoad, 0},
		{(void*)(uintptr_t)sgx_enclaveSaveInt, 0},
		{(void*)(uintptr_t)sgx_enclaveLoadInt, 0},
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
