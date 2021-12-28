
#include "DcmConverter.h"

#include <QImage>
#include "QFileInfo"

#include "DcmFile.h"
#include "DcmTagPixelData.h"

bool DcmConverter::convert(QString path) {
	QImage qImage;

	if (!qImage.load(path))
		return false;

	QImage::Format format = qImage.format();

	DcmDataset dataset;

	dataset.setTagValue("MediaStorageSOPClassUID", "1.2.840.10008.5.1.4.1.1.1");
	dataset.setTagValue("MediaStorageSOPInstanceUID", "1.2.3.4.5.6.7");
	dataset.setTagValue("StudyInstanceUID", "1.2.3.4.5.6.7.1");
	dataset.setTagValue("SeriesInstanceUID", "1.2.3.4.5.6.7.1.1");
	dataset.setTagValue("SOPClassUID", "1.2.840.10008.5.1.4.1.1.1");
	dataset.setTagValue("SOPInstanceUID", "1.2.3.4.5.6.7");
	dataset.setTagValue("PatientId", "BJ750315");
	dataset.setTagValue("PatientName", "Brown^John");
	dataset.setTagValue("PatientSex", "M");

	// write image data
	dataset.setTagValue("SamplesPerPixel", 1);
	dataset.setTagValue("PhotometricInterpretation", "MONOCHROME2");
	dataset.setTagValue("Rows", qImage.height());
	dataset.setTagValue("Columns", qImage.width());
	dataset.setTagValue("PixelSpacing", "859375\0.859375");
	dataset.setTagValue("BitsAllocated", 8);
	dataset.setTagValue("BitsStored", 8);

	dataset.setTagValue("HighBit", 7);

	DcmTagPixelData tagPixelData(DcmTagPixelData::Format_Native, DcmVr::UN);

	int byteCountPerPixel = 1; // only 8 bit image
	int bufferSize = qImage.width() * qImage.height() * byteCountPerPixel;

	char *buffer = new char[bufferSize];

	int idx = 0;

	for (int y = 0; y < qImage.height(); y++) {
		QRgb *scanLine = (QRgb*)qImage.scanLine(y);
		for (int x = 0; x < qImage.width(); x++) {
			buffer[idx++] = qGray(scanLine[x]);
		}
	}

	QByteArray byteArray((const char*)buffer, bufferSize);

	tagPixelData.setByteArray(byteArray);

	delete[] buffer;

	dataset.insert(tagPixelData);

	QFileInfo info(path);

	QString newPath = info.path() + "/" + info.baseName() + ".dcm";

	DcmFile file(newPath);

	file.write(dataset);

	return true;
}
