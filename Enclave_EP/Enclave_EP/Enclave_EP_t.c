#include "Enclave_EP_t.h"

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


typedef struct ms_EndPoint_TrustedFn_t {
	char* ms_uData;
} ms_EndPoint_TrustedFn_t;

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4127)
#pragma warning(disable: 4200)
#endif

static sgx_status_t SGX_CDECL sgx_EndPoint_TrustedFn(void* pms)
{
	ms_EndPoint_TrustedFn_t* ms = SGX_CAST(ms_EndPoint_TrustedFn_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	char* _tmp_uData = ms->ms_uData;
	size_t _len_uData = _tmp_uData ? strlen(_tmp_uData) + 1 : 0;
	char* _in_uData = NULL;

	CHECK_REF_POINTER(pms, sizeof(ms_EndPoint_TrustedFn_t));
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
	EndPoint_TrustedFn(_in_uData);
err:
	if (_in_uData) {
		memcpy(_tmp_uData, _in_uData, _len_uData);
		free(_in_uData);
	}

	return status;
}

SGX_EXTERNC const struct {
	size_t nr_ecall;
	struct {void* call_addr; uint8_t is_priv;} ecall_table[1];
} g_ecall_table = {
	1,
	{
		{(void*)(uintptr_t)sgx_EndPoint_TrustedFn, 0},
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
