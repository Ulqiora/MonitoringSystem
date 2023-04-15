extern "C" void matrix_addition(float* result, float* matrix1, float* matrix2, int rows, int cols) {
    for(int i=0; i<rows; i++) {
        for(int j=0; j<cols; j++) {
            result[i*cols + j] = matrix1[i*cols + j] + matrix2[i*cols + j];
        }
    }
}