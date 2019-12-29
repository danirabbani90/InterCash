// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2019 ITC developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "bignum.h"
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
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (0, uint256("0x00000ef5b360f1287fc2796546374122df45cf22e34030977d043ee893a762a2"));

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1577340125, // * UNIX timestamp of last checkpoint block
    0,          // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x0"));

static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1577340133,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x0"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1577340125,
    0,
    100};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xe8;
        pchMessageStart[1] = 0x8c;
        pchMessageStart[2] = 0x96;
        pchMessageStart[3] = 0xff;
        vAlertPubKey = ParseHex("04fd64ebc146cfc817c88c7e5d9ef41a8cdd31f3fe63ed942242fdce2ad2c1ac9676a0fa1825afef6612dfd74503857694293b0a2f9ac239ef1671ad3151780eb00");
        nDefaultPort = 6333;
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        nSubsidyHalvingInterval = 1050000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // Intercash: 1 day
        nTargetSpacing = 2 * 60;  // Intercash: 2 minutes
        nMaturity = 10;
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 20000000000LL * COIN;

        /** Height or Time Based Activations **/
        nLastPOWBlock = 200;
        nModifierUpdateBlock = 1; // we use the version 2 for ITC

        /**
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         *
         * 04ffff001d01044c5843454f20476572727920436f7474656e204f662043616e6164612773206c6172676573742043727970746f2043757272656e63792045786368616e676520517561647269676143582064696573206174206167652033302e
         * algorithm: quark-hash
         * merkle hash: da352915ff9eba440eab10384290cf2235c69f57d998d0d35e510c0158d00dd1
         * pszTimestamp: CEO Gerry Cotten Of Canada's largest Crypto Currency Exchange QuadrigaCX dies at age 30.
         * pubkey: 04496caa4a6d40204e26af17f286641791c51ecd052139d165f14d64fea0e3123eaf77b20516bf5eb6a261459d920765a85868248996c9a8c94d17c70434f5c58a
         * time: 1549408061
         * bits: 0x1e0ffff0
         * nonce: 830459
         * genesis_hash: 000008eede4bdf7fe9ea92e5658a6b9bf0641d3156fd97c2fdc7ce1c88a8bf19
         */
        const char* pszTimestamp = "Communities in Calderdale 'traumatised' by 2015 floods in Mytholmroyd";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("046e8845784f4ef81c1081a0bd679442bf3ad47b37cb1320702ce4e582ad8f0e122880127039b796ec47c0a4655a003136cfd01816edc7e8c8a606a5a3b46757b9") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1577340151;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 30845845;

        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0x00000ef5b360f1287fc2796546374122df45cf22e34030977d043ee893a762a2"));
        assert(genesis.hashMerkleRoot == uint256("0x16b1f5d1b55b97dc0213e34003cd5c6b76fef8ab9b2fbc282b4dbfee32db6d24"));



        vSeeds.push_back(CDNSSeedData("157.245.193.181", "157.245.193.181"));
        vSeeds.push_back(CDNSSeedData("157.245.195.2", "157.245.195.2"));// Primary node Seeder
        vSeeds.push_back(CDNSSeedData("157.245.148.114", "157.245.148.114")); //Secondary node seeder




        // Intercash addresses start with 'i'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 103);
        // Intercash script addresses start with 'c'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 88);
        // Intercash private keys start with 'K'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 46);
        // Intercash BIP32 pubkeys start with 'xpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        // Intercash BIP32 prvkeys start with 'xprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        // Intercash BIP44 coin type is '222' (0x800000de)
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0xde).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = " 043d758bfe771225aab6ff506085a253d78a8a9cb793a9823e7031c197d3181e9e06dcdd9389c716cc569734abfad862bc3246978d3329845326b1b740531f568a";
        strMasternodePoolDummyAddress = "iSJVWUkt6HtSCY2SaJ2akeyJUg8bg1hW3S";
        nStartMasternodePayments = genesis.nTime + 86400; // 24 hours after genesis creation

        nBudget_Fee_Confirmations = 6; // Number of confirmations for the finalization fee
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
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0xa5;
        pchMessageStart[1] = 0x30;
        pchMessageStart[2] = 0xc9;
        pchMessageStart[3] = 0x6f;
        vAlertPubKey = ParseHex("0409f31832a3139336ac173c0e14020b48a216b385ab56662d9873feb894bec71e7e0686a3e81ff74237b5b527907d3df73d0287d44d00a6a16e2b4b189adcbde2");
        nDefaultPort = 16333;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // Intercash: 1 day
        nTargetSpacing = 2 * 60;  // Intercash: 1 minute
        nLastPOWBlock = 200;
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 1;
        nMaxMoneyOut = 1000000000 * COIN;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1577340133;
        genesis.nNonce = 35055072;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00000170d3e3c7a30b669874987bf106c9cfeb45170ef4562ae0c2e9a6aef295"));
        


        vFixedSeeds.clear();
        vSeeds.clear();

        // Testnet Intercash addresses start with 't'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 127);
        // Testnet Intercash script addresses start with '4' or '5'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 9);
        // Testnet private keys start with 'k'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 108);
        // Testnet Intercash BIP32 pubkeys start with 'tpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        // Testnet Intercash BIP32 prvkeys start with 'tprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
        // Testnet bitcoin green BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "043d758bfe771225aab6ff506085a253d78a8a9cb793a9823e7031c197d3181e9e06dcdd9389c716cc569734abfad862bc3246978d3329845326b1b740531f568a";
        strMasternodePoolDummyAddress = "ibJ4Qad4xc77PpLzMx6rUegAs6aUPWkcUq";
        nStartMasternodePayments = genesis.nTime + 86400; // 24 hours after genesis
        nBudget_Fee_Confirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                       // here because we only have a 8 block finalization window on testnet
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
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0x35;
        pchMessageStart[1] = 0x46;
        pchMessageStart[2] = 0x89;
        pchMessageStart[3] = 0x27;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // Intercash: 1 day
        nTargetSpacing = 2 * 60;        // Intercash: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1577340125;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 27337089;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 26333;

        // assert(hashGenesisBlock == uint256("0X000002dc65b7c525dbcb7872ea3d5a3720e5938766001e308b847a0c07f9f76d"));


        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Regtest mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
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
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 61479;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
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

void SelectParams(CBaseChainParams::Network network)
{
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
