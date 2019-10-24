#pragma once
#include "Median.h"
#include <memory>
#include <string>

/**
 * @file MedianFactory.h
 * @brief Factory routines for Median 
 */

 /*! create a Median object 
     \brief create a Median object 
     \param name class name to create object of
     \return null pointer if name not found, otherwise valid unique pointer
 */
std::unique_ptr<Median> create_Median (const std::string& name);