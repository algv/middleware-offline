#ifndef __PDF_SIGNATURE_H
#define __PDF_SIGNATURE_H

#include "Export.h"
#include <vector>
#include <utility>

#include "ByteArray.h"
#include "APLCard.h"
#include <openssl/pkcs7.h>

class PDFRectangle;
class PDFDoc;
class GooString;

namespace eIDMW
{

	class CReader;

	typedef struct
	{
		unsigned char * img_data;
		unsigned long img_length;
		int img_height;
		int img_width;
	} Pixmap;

	class PDFSignature
	{
	public:
		EIDMW_APL_API PDFSignature();
		EIDMW_APL_API PDFSignature(const char *path);
		EIDMW_APL_API ~PDFSignature();

		//Batch Operations (with PIN caching)
		EIDMW_APL_API void batchAddFile(char *file_path, bool last_page);
		EIDMW_APL_API void enableTimestamp();

		EIDMW_APL_API void setVisible(unsigned int page, int sector);
		EIDMW_APL_API void setVisibleCoordinates(unsigned int page, double coord_x, double coord_y);
		EIDMW_APL_API char *getOccupiedSectors(int page);
		EIDMW_APL_API int getPageCount();
		EIDMW_APL_API int getOtherPageCount(const char *input_path);
		void setCard(APL_Card *card) { m_card = card; };

		//General interface to signing in single file-mode or batch-mode
		EIDMW_APL_API int signFiles(const char *location, const char *reason,
			const char *outfile_path);
        EIDMW_APL_API bool isLandscapeFormat();
		EIDMW_APL_API void setCustomImage(unsigned char *img_data, unsigned long img_length);
		EIDMW_APL_API void enableSmallSignature();

        bool getBatch_mode();
        void setBatch_mode( bool batch_mode );

        /* isCertificate */
        bool isExternalCertificate();
        CByteArray getIsExtCertificate();
        void setIsExtCertificate( bool in_IsExternalCertificate );

        /* Certificate */
        CByteArray getExternCertificate();
        void setExternCertificate( CByteArray certificate );

        /* Certificate CA */
        CByteArray getExternCertificateCA();
        void setExternCertificateCA( CByteArray certificateCA );

        /* Hash */
        CByteArray getHash();
        void setHash( CByteArray in_hash );
        void computeHash( unsigned char *data, unsigned long dataLen
                        , CByteArray certificate
                        , CByteArray CA_certificate );

        /* signClose */
        int signClose( CByteArray signature );

	private:
		void getCitizenData();
		std::string generateFinalPath(const char *output_dir, const char *path);
		PDFRectangle computeSigLocationFromSector(double, double, int);
		PDFRectangle computeSigLocationFromSectorLandscape(double, double, int);
		int signSingleFile(const char *location, const char *reason,
			const char *outfile_path);

		APL_Card *m_card;
		PDFDoc *m_doc;

		const char * m_pdf_file_path;

		// These values are constants because the actual construction of the signature appearance in pteid-poppler assumes
		// this amount of available space
		static const double sig_height;
		static const double sig_width;
		static const double tb_margin;

		static const int lr_margin = 30;

		char *m_civil_number;
		char *m_citizen_fullname;
		unsigned int m_page, m_sector;
		double location_x, location_y;
		bool m_visible;
		bool m_isLandscape;
		bool m_batch_mode;
		bool m_timestamp;
		bool m_small_signature;
		std::vector< std::pair<char *, bool> > m_files_to_sign;
		Pixmap my_custom_image;

        PKCS7 *m_pkcs7;
        CByteArray m_externCertificate;
        CByteArray m_externCertificateCA;
        CByteArray m_hash;
        PKCS7_SIGNER_INFO *m_signerInfo;
        GooString *m_outputName;
        bool m_signStarted;
        bool m_isExternalCertificate;
	};

}

#endif
