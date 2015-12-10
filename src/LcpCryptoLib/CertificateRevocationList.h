#ifndef __CERTIFICATE_REVOCATION_LIST_H__
#define __CERTIFICATE_REVOCATION_LIST_H__

#include "ICertificate.h"

namespace lcp
{
    class CertificateRevocationList : public ICertificateRevocationList
    {
    public:
        CertificateRevocationList() = default;
        explicit CertificateRevocationList(const Buffer & crlRaw);
        
        // ICertificateRevocationList
        virtual void UpdateRevocationList(const Buffer & crlRaw);
        virtual std::string ThisUpdateDate() const;
        virtual bool HasNextUpdateDate() const;
        virtual std::string NextUpdateDate() const;
        virtual bool SerialNumberRevoked(const std::string & serialNumber) const;
        virtual const StringsSet & RevokedSerialNumbers() const;

    private:
        std::string m_thisUpdate;
        std::string m_nextUpdate;
        StringsSet m_revokedSerialNumbers;
    };
}

#endif //__CERTIFICATE_REVOCATION_LIST_H__
