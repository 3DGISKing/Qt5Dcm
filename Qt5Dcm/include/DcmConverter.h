#ifndef DCMCONVERTER_H
#define DCMCONVERTER_H

#include "DcmCoreApi.h"

#include <QString>

class DCM_CORE_API DcmConverter
{
public:

	/**
	* Convert image to dcm
	* \return True if success.
	*/
	static bool convert(QString path);
};

#endif // DCMCONVERTER_H
