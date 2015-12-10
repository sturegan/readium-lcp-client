#ifndef __CRL_REVOCATION_LIST_UPDATER_H__
#define __CRL_REVOCATION_LIST_UPDATER_H__

#include <memory>
#include <mutex>
#include <condition_variable>
#include "ICertificate.h"
#include "Public/INetProvider.h"

namespace lcp
{
    class ThreadTimer;
    class CrlDownloader;
    class IDownloadRequest;
    class SimpleMemoryWritableStream;

    class CrlUpdater : public INetProviderCallback
    {
    public:
        CrlUpdater(
            INetProvider * netProvider,
            ICertificateRevocationList * revocationList,
            ThreadTimer * threadTimer
            );

        void Update();
        void Cancel();

        void UpdateCrlDistributionPoints(ICrlDistributionPoints * distributionPoints);
        bool ContainsUrl(const std::string & url);
        bool ContainsAnyUrl() const;

        // INetProviderCallback
        virtual void OnRequestStarted(INetRequest * request);
        virtual void OnRequestProgressed(INetRequest * request, float progress);
        virtual void OnRequestCanceled(INetRequest * request);
        virtual void OnRequestEnded(INetRequest * request, Status result);

    private:
        void Download(const std::string & url);
        void ResetNextUpdate();

    private:
        StringsList m_crlUrls;
        INetProvider * m_netProvider;
        ICertificateRevocationList * m_revocationList;
        ThreadTimer * m_threadTimer;

        std::unique_ptr<SimpleMemoryWritableStream> m_crlStream;
        std::unique_ptr<IDownloadRequest> m_downloadRequest;
        Status m_currentRequestStatus;

        bool m_requestRunning;
        mutable std::mutex m_downloadSync;
        std::condition_variable m_conditionDownload;

        static const int TenMinutesPeriod = 1000 * 60 * 10;
    };
}

#endif //__CRL_REVOCATION_LIST_UPDATER_H__
