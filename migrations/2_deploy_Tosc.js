//계약정보
const TOSC = artifacts.require('./../contracts/TOSC')
const functions = artifacts.require('./../contracts/functions')


module.exports = async function(deployer) {
	// Use deployer to state migration tasks.

    // const initialSupply = "2130000000";
    // const tokenName = "TOSC";
    // const tokenSymbol = "TOSC";

	//TOSC 배포
    // deployer.deploy(TOSC, initialSupply, tokenName, tokenSymbol);

    const ToscAddress = "0xd50649AAb1D39d68BC965E0F6D1cfe0010e4908b";
    deployer.deploy(functions, ToscAddress);
};
