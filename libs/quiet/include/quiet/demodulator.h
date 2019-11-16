#include <assert.h>

#include "quiet/common.h"

#define cfloat float
// should be cfloat float complex

demodulator *demodulator_create(const demodulator_options *opt);
size_t demodulator_recv(demodulator *d, const sample_t *samples, size_t sample_len,
                               cfloat *symbols);
size_t demodulator_flush(demodulator *d, cfloat *symbols);
void demodulator_destroy(demodulator *d);
size_t demodulator_flush_symbol_len(const demodulator *d);
