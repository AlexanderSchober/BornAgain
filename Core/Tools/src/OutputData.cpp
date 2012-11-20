#include "OutputData.h"
#include "Exceptions.h"
#include "Numeric.h"
#include <cmath>
#include <fftw3.h>


void toFftw3Array(complex_t *source, size_t length, fftw_complex *destination);
void fromFftw3Array(fftw_complex *source, size_t length, complex_t *destination);

/* ************************************************************************* */
// double the bin size for each dimension
/* ************************************************************************* */
OutputData<double> *doubleBinSize(const OutputData<double> &source)
{
    OutputData<double> *p_result = new OutputData<double>;
    size_t dimension = source.getRank();
    std::vector<size_t> source_sizes = source.getAllSizes();
    std::vector<bool> needs_resizing;
    // create new axes
    for (size_t i=0; i<dimension; ++i) {
        needs_resizing.push_back(source_sizes[i] > 1);
        const NamedVector<double> *source_axis = dynamic_cast<const NamedVector<double> *>(source.getAxis(i));
        p_result->addAxis(source_axis->createDoubleBinSize());
    }
    // calculate new data content
    OutputData<double>::const_iterator it_source = source.begin();
    while (it_source != source.end()) {
        std::vector<int> source_indices = source.toCoordinates(it_source.getIndex());
        std::vector<int> dest_indices;
        double boundary_factor = 1.0;
        for (size_t i=0; i<source_indices.size(); ++i) {
            dest_indices.push_back(source_indices[i]/2);
            if (needs_resizing[i] &&
                    source_sizes[i]%2 == 1 &&
                    source_indices[i] == (int)source_sizes[i]-1) {
                boundary_factor *= 2.0;
            }
        }
        (*p_result)[p_result->toIndex(dest_indices)] = boundary_factor*(*it_source++);
    }
    return p_result;
}

void fourierTransform(const OutputData<double>& source, OutputData<complex_t> *p_destination)
{
    // initialize dimensions
    std::vector<size_t> dimensions = source.getAllSizes();
    size_t rank = dimensions.size();
    int *n_real_dims = new int[rank];
    int *n_complex_dims = new int[rank];
    size_t total_real_size = 1;
    size_t total_complex_size = 1;
    for (size_t i=0; i<rank; ++i) {
        total_real_size *= (n_real_dims[i] = (int)dimensions[i]);
        if (i<rank-1) total_complex_size *= (n_complex_dims[i] = (int)dimensions[i]);
        else total_complex_size *= (n_complex_dims[i] = (int)dimensions[i]/2 +1);
    }
    // allocate result
    if (p_destination->getAllocatedSize() != total_complex_size) {
        p_destination->setAxisSizes(rank, n_complex_dims);
    }
    //  initialize temporary arrays
    double *input = fftw_alloc_real(total_real_size);
    fftw_complex *output = fftw_alloc_complex(total_complex_size);
    fftw_plan plan = fftw_plan_dft_r2c(rank, n_real_dims, input, output, FFTW_ESTIMATE);
    source.fillRawDataArray(input);

    // execute the plan
    fftw_execute(plan);
    // put output into result map
    complex_t *output2 = new complex_t[total_complex_size];
    fromFftw3Array(output, total_complex_size, output2);
    p_destination->setRawDataArray(output2);
    delete[] output2;

    // free allocated objects
    fftw_destroy_plan(plan);
    fftw_free(input);
    fftw_free(output);
    delete[] n_real_dims;
    delete[] n_complex_dims;
}

void fourierTransformR(const OutputData<complex_t>& source, OutputData<double> *p_destination)
{
    // initialize dimensions
    std::vector<size_t> dimensions = p_destination->getAllSizes();
    size_t rank = (int)dimensions.size();
    int *n_real_dims = new int[rank];
    int *n_complex_dims = new int[rank];
    size_t total_real_size = 1;
    size_t total_complex_size = 1;
    for (size_t i=0; i<rank; ++i) {
        total_real_size *= (n_real_dims[i] = (int)dimensions[i]);
        if (i<rank-1) total_complex_size *= (n_complex_dims[i] = (int)dimensions[i]);
        else total_complex_size *= (n_complex_dims[i] = (int)dimensions[i]/2 +1);
    }
    // allocate result
    if (source.getAllocatedSize() != total_complex_size) {
        throw ClassInitializationException("Inverse Fourier transform requires properly allocated map sizes");
    }
    //  initialize temporary arrays
    double *output = fftw_alloc_real(total_real_size);
    fftw_complex *input = fftw_alloc_complex(total_complex_size);
    fftw_plan plan = fftw_plan_dft_c2r(rank, n_real_dims, input, output, FFTW_ESTIMATE);
    complex_t *input2 = new complex_t[total_complex_size];
    source.fillRawDataArray(input2);
    toFftw3Array(input2, total_complex_size, input);
    delete[] input2;

    // execute the plan
    fftw_execute(plan);
    // put output into result map and rescale
    p_destination->setRawDataArray(output);
    double scaling_factor = 1.0/p_destination->getAllocatedSize();
    p_destination->scaleAll(scaling_factor);

    // free allocated objects
    fftw_destroy_plan(plan);
    fftw_free(input);
    fftw_free(output);
    delete[] n_real_dims;
    delete[] n_complex_dims;
}

OutputData<double> *getRealPart(const OutputData<complex_t> &source)
{
    OutputData<double> *p_result = new OutputData<double>();
    for (size_t i=0; i<source.getRank(); ++i) {
        p_result->addAxis(source.getAxis(i)->clone());
    }
    OutputData<complex_t>::const_iterator it_source = source.begin();
    OutputData<double>::iterator it_result = p_result->begin();
    while (it_source != source.end()) {
        *it_result = it_source->real();
        ++it_source, ++it_result;
    }
    return p_result;
}

OutputData<double>* getImagPart(const OutputData<complex_t>& source)
{
    OutputData<double> *p_result = new OutputData<double>();
    for (size_t i=0; i<source.getRank(); ++i) {
        p_result->addAxis(source.getAxis(i)->clone());
    }
    OutputData<complex_t>::const_iterator it_source = source.begin();
    OutputData<double>::iterator it_result = p_result->begin();
    while (it_source != source.end()) {
        *it_result = it_source->real();
        ++it_source, ++it_result;
    }
    return p_result;
}

OutputData<double>* getModulusPart(const OutputData<complex_t>& source)
{
    OutputData<double> *p_result = new OutputData<double>();
    for (size_t i=0; i<source.getRank(); ++i) {
        p_result->addAxis(source.getAxis(i)->clone());
    }
    OutputData<complex_t>::const_iterator it_source = source.begin();
    OutputData<double>::iterator it_result = p_result->begin();
    while (it_source != source.end()) {
        *it_result = std::abs(*it_source);
        ++it_source, ++it_result;
    }
    return p_result;
}

void toFftw3Array(complex_t *source, size_t length, fftw_complex *destination)
{
    for (size_t i=0; i<length; ++i) {
        destination[i][0] = source[i].real();
        destination[i][1] = source[i].imag();
    }
}

void fromFftw3Array(fftw_complex *source, size_t length, complex_t *destination)
{
    for (size_t i=0; i<length; ++i) {
        destination[i].real() = source[i][0];
        destination[i].imag() = source[i][1];
    }
}

