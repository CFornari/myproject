#include "matrix_sensor.h"

MatrixSensor::MatrixSensor() : _adc_num(4),
                               _adc_clk_div(8),
                               _col(0),
                               _row(0),
                               _cell(0)
{
    _adc_addr = new uint16_t[_adc_num](); // Allocate space and init with all values with 0.
}

MatrixSensor::~MatrixSensor()
{
    delete _adc_addr;
}

/**@brief 	Reset column, row and cell values to zero.
 * @param	none
 * @retval	void
 */
void MatrixSensor::reset()
{
    _col = 0;
    _row = 0;
    _cell = 0;
    digitalWrite(NX_COL, false);
	digitalWrite(RT_COL, false);
	digitalWrite(NX_ROW, false);
	digitalWrite(RT_ROW, false);
}

void MatrixSensor::resetCol()
{
    digitalWrite(RT_COL, false);
    _col = 0;    
}

void MatrixSensor::nextCol()
{
    _col++;
}

uint32_t MatrixSensor::getCol()
{
    return _col;
}

void MatrixSensor::resetRow()
{
    digitalWrite(RT_ROW, false);
    _row = 0;
}

void MatrixSensor::nextRow()
{
    _row++;
}

uint32_t MatrixSensor::getRow()
{
    return _row;
}

/**@brief 	Returns the last cell measured with readCell().
 * @param	none
 * 
 * Returns the last value 
 * This code disables all the interrupts and the wifi connection.
 */
void MatrixSensor::readSingleCell()
{
    // Check if wifi is enable.
    bool wifi_state = false;
    if (WifiStation.isEnabled())
    {
        WifiStation.enable(false);
        wifi_state = true;
    }

    ets_intr_lock(); //close interrupt
    readCell();
    ets_intr_unlock(); //open interrupt

    if (wifi_state)
        WifiStation.enable(true); // Enable wifi if it was previously enabled.
}

/**@brief 	Returns the last cell measured with readCell().
 * @param	none
 * 
 * This function DOES NOT execute a measurement, it rather just returns last 
 * value measured and stored.
 * The function will return 0 if its called immediatly after a @code reset().
 */
uint16_t MatrixSensor::getLastCell()
{
    return _cell;
}

/**@brief   Measure all the cells.
 * @param	none
 * 
 * Reads the ADC value of each cell in the matrix.
 * This code disables all the interrupts and the wifi connection during the 
 * measurements.
 */
void MatrixSensor::readMatrix()
{
    // Check if wifi is enable.
    bool wifi_state = false;
    if (WifiStation.isEnabled())
    {
        WifiStation.enable(false);
        wifi_state = true; // For enabling at the function's end.
    }

    ets_intr_lock(); //close interrupt

    reset();
    for (uint32_t i = 0; i < MAX_COLS; i++)
    {
        for (uint32_t j = 0; j < MAX_ROWS; j++)
        {
            readCell();
            _matrix[i][j] = _cell;
            nextRow();
        }
        nextCol();
        resetRow();
    }

    ets_intr_unlock(); //open interrupt

    if (wifi_state)
        WifiStation.enable(true); // Enable wifi if it was previously enabled.
}

/**@brief 	Reads the ADC value of a single cell, at the current column and row.
 * @param	none
 * 
 * The value is stored in a private class variable
 * The code calling the this function needs to disable all the interrupts and 
 * the wifi connection.
 * 
 * @b Example: This is what happens inside @code readSingleCell().
 * @code
 *  // Check if wifi is enable.
 *  bool wifi_state = false;
 *  if(WifiStation.isEnabled())
 *  {
 *      WifiStation.enable(false);
 *      wifi_state = true;
 *  }       
 * 
 *  ets_intr_lock(); //close interrupt
 *  readCell();
 *  ets_intr_unlock(); //open interrupt
 *  
 *  if(wifi_state)
 *      WifiStation.enable(true); // Enable wifi if it was previously enabled.
 * @endcode
 * 
 * The real purpose of this function is to enable the user to perform a burst 
 * read in all matrix without the overhead of disabling the pheripherals in 
 * each cell measurement. The @code readMatrix() uses this function for that purpose.
 */
void MatrixSensor::readCell()
{
    system_adc_read_fast(_adc_addr, _adc_num, _adc_clk_div);
    _cell = 0;
    for (uint32_t i = 0; i < _adc_num; i++)
    {
        _cell += _adc_addr[i];
    }
    _cell /= _adc_num;
}
