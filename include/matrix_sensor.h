#ifndef __MATRIX_SENSOR_H__
#define __MATRIX_SENSOR_H__

#include "global_core.h"

class MatrixSensor
{
public:
    explicit MatrixSensor();
    ~MatrixSensor();

    void reset();

    void resetCol();
    void nextCol();
    uint32_t getCol();

    void resetRow();
    void nextRow();
    uint32_t getRow();

    void readSingleCell();
    uint16_t getLastCell();

    void readMatrix();
    

private:
    void readCell();

    uint32_t _col;
    uint32_t _row;
    uint16_t _cell; // needs to work with the precission.
    uint16_t _matrix[MAX_COLS][MAX_ROWS]; // stores one frame per time.

    uint16 *_adc_addr;
    uint16 _adc_num;
    uint8 _adc_clk_div;
};

#endif