// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2017-2018 The T.OS developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */

/*
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
*/

static Checkpoints::MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
        ( 0, uint256("0xfbee487873531d16bcb6dfa67e0bf02c43a6697c67ba2c03a432f156c5149093"))
        ;
static const Checkpoints::CCheckpointData data = {
        &mapCheckpoints,
        1502464687, // * UNIX timestamp of last checkpoint block
        0,   // * total number of transactions between genesis and last checkpoint
                    //   (the tx=... number in the SetBestChain debug.log lines)
        3000.0     // * estimated number of transactions per day after checkpoint
    };

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
        boost::assign::map_list_of
        ( 0, uint256("0x30cd76aa0af5391c07a0377c9c17bfdf004ca138b7c8e2c93eddace12a0e7c0e"))
        ( 1, uint256("0xf5279e96b52328af723059e83c3f9c6cb38a193506f3634538e86cf63a4bbd69"))
        ( 150, uint256("0x3d62ee7040be4159627ee7e760c6538ca8b216bb77188cc035a9b53cbc3dac8a"))
        ;
static const Checkpoints::CCheckpointData dataTestnet = {
        &mapCheckpointsTestnet,
        1535352586,
        151,
        900
    };

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
        boost::assign::map_list_of
        ( 0, uint256("0b3277b24ac1e4a11f4c446f6b6bd439ca3ccc543012abcd567890abcdef201a"))
        ;
static const Checkpoints::CCheckpointData dataRegtest = {
        &mapCheckpointsRegtest,
        0,
        0,
        0
    };

class CMainParams : public CChainParams {
public:
    CMainParams() {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /** 
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xd8;
        pchMessageStart[1] = 0xce;
        pchMessageStart[2] = 0xaf;
        pchMessageStart[3] = 0xeb;
        vAlertPubKey = ParseHex("15689bgec1gf6659382078g2b78241c8216de7b939e03909a67962e0ea1f61deb649f6bc3f4cef38c5g46615f62fd223ef6d495eg8cb1c9e689b5d813c7cg22e6g");
        nDefaultPort = 24147;
        bnProofOfWorkLimit = ~uint256(0) >> 20;
        nSubsidyHalvingInterval = 5250000;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 4 * 60 * 60;
        nTargetSpacing = 1 * 60; // 1 minutes
        nMaxTipAge = 24 * 60 * 60;

        /**
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         * 
         * CBlock(hash=000000000019d6, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=4a5e1e, nTime=1231006505, nBits=1d00ffff, nNonce=2083236893, vtx=1)
         *   CTransaction(hash=4a5e1e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
         *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73)
         *     CTxOut(nValue=50.00000000, scriptPubKey=0x5F1DF16B2B704C8A578D0B)
         *   vMerkleTree: 4a5e1e
         */
        const char* pszTimestamp = "tos genesis block";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 100 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1502464687;
        genesis.nBits    = 0x1e0ffff0;
        genesis.nNonce   = 191554;

/*
            printf("nTime = %u \n", genesis.nTime);
            printf("nNonce = %u \n", genesis.nNonce);
            printf("GetHash = %s\n", genesis.GetHash().ToString().c_str());
            printf("hashMerkleroot = %s \n", genesis.hashMerkleRoot.ToString().c_str());
            printf("\n");
*/

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0xfbee487873531d16bcb6dfa67e0bf02c43a6697c67ba2c03a432f156c5149093"));
        assert(genesis.hashMerkleRoot == uint256("0xb55e5b7c9d421c7120e93cbeafc9de16b5096dc8880a1cb2a7e2a04b3fd290d8"));

        vSeeds.push_back(CDNSSeedData("tosblock.com", "dnsseed.tosblock.com"));
        vSeeds.push_back(CDNSSeedData("tosblock.com", "dnsseed2.tosblock.com"));
        vSeeds.push_back(CDNSSeedData("tosblock.com", "dnsseed3.tosblock.com"));
        vSeeds.push_back(CDNSSeedData("tosblock.com", "dnsseed4.tosblock.com"));
        vSeeds.push_back(CDNSSeedData("tosblock.com", "dnsseed5.tosblock.com"));


        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,66);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,5);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,194);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = true;
        fTestnetToBeDeprecatedFieldRPC = false;

        // TOSC: Mainnet v2 enforced as of block 560k
        nEnforceV2AfterHeight = 560000;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const 
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0xbc;
        pchMessageStart[1] = 0xad;
        pchMessageStart[2] = 0xaf;
        pchMessageStart[3] = 0xc4;
        vAlertPubKey = ParseHex("0449623fc74489a947c4b15d579115591add020e53b3490bf47297dfa3762250625f8ecc2fb4fc59f69bdce8f7080f3167808276ed2c79d297054367566038aa82");
        nDefaultPort = 33813;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 4 * 60 * 60;
        nTargetSpacing = 1 * 60; // 1 minutes
        nMaxTipAge = 0x7fffffff;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1502465579;
        genesis.nNonce = 192308;
        hashGenesisBlock = genesis.GetHash();
        //assert(hashGenesisBlock == uint256("0x30cd76aa0af5391c07a0377c9c17bfdf004ca138b7c8e2c93eddace12a0e7c0e"));

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("tosctools.com", "testnet-dnsseed.tosblock.com"));
        vSeeds.push_back(CDNSSeedData("tosblock.com", "testnet-dnsseed2.tosblock.com"));
        vSeeds.push_back(CDNSSeedData("tosblock.com", "testnet-dnsseed3.tosblock.com"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        // TOSC: v2 enforced using Bitcoin's supermajority rule
        nEnforceV2AfterHeight = -1;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const 
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xfb;
        pchMessageStart[1] = 0xaf;
        pchMessageStart[2] = 0xc6;
        pchMessageStart[3] = 0xcb;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 4 * 60 * 60;
        nTargetSpacing = 1 * 60; // 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        nMaxTipAge = 24 * 60 * 60;
        genesis.nTime = 1296688602;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 0;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 33888;
        //assert(hashGenesisBlock == uint256("0x530827f38f93b43ed12af0b3ad25a288dc02ed74d6d7857862df51fc56c416f9"));

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Regtest mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;

        // TOSC: v2 enforced using Bitcoin's supermajority rule
        nEnforceV2AfterHeight = -1;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const 
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams {
public:
    CUnitTestParams() {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 18445;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Unit test mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;

        // TOSC: v2 enforced using Bitcoin's supermajority rule
        nEnforceV2AfterHeight = -1;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const 
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval)  { nSubsidyHalvingInterval=anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority)  { nEnforceBlockUpgradeMajority=anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority)  { nRejectBlockOutdatedMajority=anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority)  { nToCheckBlockUpgradeMajority=anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks)  { fDefaultConsistencyChecks=afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) {  fAllowMinDifficultyBlocks=afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams *pCurrentParams = 0;

CModifiableParams *ModifiableParams()
{
   assert(pCurrentParams);
   assert(pCurrentParams==&unitTestParams);
   return (CModifiableParams*)&unitTestParams;
}

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams &Params(CBaseChainParams::Network network) {
    switch (network) {
        case CBaseChainParams::MAIN:
            return mainParams;
        case CBaseChainParams::TESTNET:
            return testNetParams;
        case CBaseChainParams::REGTEST:
            return regTestParams;
        case CBaseChainParams::UNITTEST:
            return unitTestParams;
        default:
            assert(false && "Unimplemented network");
            return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network) {
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
