// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    // How many times we expect transactions after the last checkpoint to
    // be slower. This number is a compromise, as it can't be accurate for
    // every system. When reindexing from a fast disk with a slow CPU, it
    // can be up to 20, while when downloading from a slow network with a
    // fast multicore CPU, it won't be much higher than 1.
    static const double fSigcheckVerificationFactor = 5.0;


    struct CCheckpointData {
        const MapCheckpoints *mapCheckpoints;
        int64 nTimeLastCheckpoint;
        int64 nTransactionsLastCheckpoint;
        double fTransactionsPerDay;
    };

    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
            ( 0, uint256("0xfbee487873531d16bcb6dfa67e0bf02c43a6697c67ba2c03a432f156c5149093"))
            ( 1, uint256("0x4b00d48407fcbc01f44b32774bcf94bdb9f6a031c9e784d6147d05e5f4658f24"))
            ( 1500, uint256("0x5d24dbb0076a410315237e9a87934ec288ffda069fca554cb14228d3ebdf8f38"))
            ( 4027, uint256("0x721df1d89abb4fe04d9c5bd05c5b4a45626d9b963cb040fc9885a397b9445396"))
            ( 8054, uint256("0x5fa647d4616852d9ebc98984be3bd371c72f7e58d6b2c31d1bfce1bac113adf8"))
            ( 15000, uint256("0x6562d0eb919556881731e4224080c341ca9a90289acfedd7d533ad584481a974"))
            ( 35000, uint256("0xc25bc464669b38988f4a175c2d3e28b167d2de3006bbd2d8917d299a9533a7a1"))
            ( 84779, uint256("0x661a7d319657e3b50b30a7ea3a4cd608fd3ed8bb330c475caa63088db19a995f"))
            ( 145099, uint256("0xd8e70d2331e64819d74abbb5e08e7fd0f325d54327bca741914c7f3fceceed7b"))
            ( 205419, uint256("0x3cf91f993c3cfd2abb89268ce241738aaab599737e4671b50c267c1bd7c84852"))
            ( 265739, uint256("0x505e59504efae1713a38f184e0feaf1d584e8021e02733e8d1bf1e5f5fa439e2"))
            ( 326059, uint256("0x07c57cbc672699224d1546d433edb07fa97d3bbb9fd6462895ef6e0ee94a75e2"))
            ( 386379, uint256("0x5ab7dd02338040064165c991e2a08315e741721c615cd0e94e21ff415be46e2b"))
            ( 446699, uint256("0x8f20e8e29ffa8d840c6fdbe59525e2cfd02e3b2be919b544a348b1f69f63cb6d"))
            ( 477000, uint256("0x1a6a858f7ba91c5528689dc5a8a63e6dc43c0af9b2133f2e0edba0e3028e3b00"))
	;
    static const CCheckpointData data = {
        &mapCheckpoints,
        1533652910, // * UNIX timestamp of last checkpoint block
        496817,    // * total number of transactions between genesis and last checkpoint
                    //   (the tx=... number in the SetBestChain debug.log lines)
        3000.0     // * estimated number of transactions per day after checkpoint
    };

    static MapCheckpoints mapCheckpointsTestnet = 
        boost::assign::map_list_of
            ( 0, uint256("0x30cd76aa0af5391c07a0377c9c17bfdf004ca138b7c8e2c93eddace12a0e7c0e"))
            ( 1, uint256("0xf5279e96b52328af723059e83c3f9c6cb38a193506f3634538e86cf63a4bbd69"))
            ( 150, uint256("0x3d62ee7040be4159627ee7e760c6538ca8b216bb77188cc035a9b53cbc3dac8a"))
        ;
    static const CCheckpointData dataTestnet = {
        &mapCheckpointsTestnet,
        1535352586,
        151,
        900
    };

    const CCheckpointData &Checkpoints() {
        if (fTestNet)
            return dataTestnet;
        else
            return data;
    }

    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (fTestNet) return true; // Testnet has no checkpoints
        if (!GetBoolArg("-checkpoints", true))
            return true;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
        if (i == checkpoints.end()) return true;
        return hash == i->second;
    }

    // Guess how far we are in the verification process at the given block index
    double GuessVerificationProgress(CBlockIndex *pindex) {
        if (pindex==NULL)
            return 0.0;

        int64 nNow = time(NULL);

        double fWorkBefore = 0.0; // Amount of work done before pindex
        double fWorkAfter = 0.0;  // Amount of work left after pindex (estimated)
        // Work is defined as: 1.0 per transaction before the last checkoint, and
        // fSigcheckVerificationFactor per transaction after.

        const CCheckpointData &data = Checkpoints();

        if (pindex->nChainTx <= data.nTransactionsLastCheckpoint) {
            double nCheapBefore = pindex->nChainTx;
            double nCheapAfter = data.nTransactionsLastCheckpoint - pindex->nChainTx;
            double nExpensiveAfter = (nNow - data.nTimeLastCheckpoint)/86400.0*data.fTransactionsPerDay;
            fWorkBefore = nCheapBefore;
            fWorkAfter = nCheapAfter + nExpensiveAfter*fSigcheckVerificationFactor;
        } else {
            double nCheapBefore = data.nTransactionsLastCheckpoint;
            double nExpensiveBefore = pindex->nChainTx - data.nTransactionsLastCheckpoint;
            double nExpensiveAfter = (nNow - pindex->nTime)/86400.0*data.fTransactionsPerDay;
            fWorkBefore = nCheapBefore + nExpensiveBefore*fSigcheckVerificationFactor;
            fWorkAfter = nExpensiveAfter*fSigcheckVerificationFactor;
        }

        return fWorkBefore / (fWorkBefore + fWorkAfter);
    }

    int GetTotalBlocksEstimate()
    {
        if (fTestNet) return 0; // Testnet has no checkpoints
        if (!GetBoolArg("-checkpoints", true))
            return 0;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        return checkpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (fTestNet) return NULL; // Testnet has no checkpoints
        if (!GetBoolArg("-checkpoints", true))
            return NULL;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }
}
