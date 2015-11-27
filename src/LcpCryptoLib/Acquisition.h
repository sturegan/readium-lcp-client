#ifndef __LCP_ACQUISITION_H__
#define __LCP_ACQUISITION_H__

#include <string>
#include "Public/IAcquistion.h"
#include "Public/IAcquistionCallback.h"
#include "Public/INetProvider.h"
#include "Public/IFileSystemProvider.h"
#include "Public/ILicense.h"

namespace lcp
{
    class Acquisition : public IAcquisition, public INetProviderCallback
    {
    public:
        Acquisition(
            ILicense * license,
            IFileSystemProvider * fileSystemProvider,
            INetProvider * netProvider,
            const std::string & publicationPath
            );

        virtual Status Start(IAcquisitionCallback * callback);
        virtual void Cancel();
        virtual std::string PublicationPath() const;
        virtual std::string SuggestedFileName() const;

    public:
        // INetProviderCallback
        virtual void OnRequestStarted(INetRequest * request);
        virtual void OnRequestProgressed(INetRequest * request, float progress);
        virtual void OnRequestCancelled(INetRequest * request);
        virtual void OnRequestEnded(INetRequest * request, Status result);

    public:
        static const char * PublicationType;

    private:
        ILicense * m_license;
        IFileSystemProvider * m_fileSystemProvider;
        INetProvider * m_netProvider;
        std::string m_publicationPath;

        IAcquisitionCallback * m_callback;
        std::unique_ptr<IFile> m_file;
        std::unique_ptr<IDownloadRequest> m_request;

    private:
        static const float DownloadCoefficient;
    };
}

#endif //__LCP_ACQUISITION_H__