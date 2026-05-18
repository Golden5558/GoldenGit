import { expect } from "chai";
import { ethers } from "hardhat";
import { CercleToken } from "../typechain-types";
import { HardhatEthersSigner } from "@nomicfoundation/hardhat-ethers/signers";

describe("CercleToken", function () {
  let cercleToken: CercleToken;
  let owner: HardhatEthersSigner;
  let patient1: HardhatEthersSigner;
  let patient2: HardhatEthersSigner;
  let datasetHash: string;

  async function deployCercleTokenFixture() {
    const signers = await ethers.getSigners();
    const owner = signers[0];
    const patient1 = signers[1];
    const patient2 = signers[2];
  

    const CercleTokenFactory = await ethers.getContractFactory("CercleToken");
    const cercleToken = await CercleTokenFactory.deploy() as CercleToken;

    const datasetHash = ethers.keccak256(ethers.toUtf8Bytes("PatientData1"));

    return { cercleToken, owner, patient1, patient2, datasetHash };
  }

  async function deployWithAuthorizedPatients() {
    const baseFixture = await deployCercleTokenFixture();
    await baseFixture.cercleToken.connect(baseFixture.owner).setAuthorizedPatient(baseFixture.patient1.address, true);
    await baseFixture.cercleToken.connect(baseFixture.owner).setAuthorizedPatient(baseFixture.patient2.address, true);
    return baseFixture;
  }

  async function deployAuthorizedPatientsWithTokens() {
    const baseFixture = await deployWithAuthorizedPatients();
    await baseFixture.cercleToken.connect(baseFixture.patient1).rewardForDataDownload(
      baseFixture.patient1.address,
      baseFixture.datasetHash
    );
    await baseFixture.cercleToken.connect(baseFixture.patient2).rewardForDataDownload(
      baseFixture.patient2.address,
      baseFixture.datasetHash
    );
    return baseFixture;
  }

  describe("Deployment and basic properties", function () {
    it("Should deploy with correct initial values", async function () {
      const { cercleToken } = await deployCercleTokenFixture();
      
      expect(await cercleToken.name()).to.equal("CercleToken");
      expect(await cercleToken.symbol()).to.equal("CERCLE");
      expect(await cercleToken.totalSupply()).to.equal(0);
    });

    it("Should implement Soul Bound Token properties", async function () {
      const { cercleToken } = await deployCercleTokenFixture();
      
      expect(await cercleToken.isSoulBound()).to.be.true;
      expect(await cercleToken.canTransfer()).to.be.false;
    });
  });

  describe("Authorization management", function () {
    it("Should handle patient authorization correctly", async function () {
      const { cercleToken, owner, patient1 } = await deployCercleTokenFixture();

      // Test initial state
      expect(await cercleToken.authorizedPatient(patient1.address)).to.be.false;

      // Test successful authorization
      await expect(cercleToken.connect(owner).setAuthorizedPatient(patient1.address, true))
        .to.emit(cercleToken, "PatientAuthorizationChanged")
        .withArgs(patient1.address, true);

      expect(await cercleToken.authorizedPatient(patient1.address)).to.be.true;

      // Test zero address validation
      await expect(cercleToken.connect(owner).setAuthorizedPatient(ethers.ZeroAddress, true))
        .to.be.revertedWithCustomError(cercleToken, "InvalidAddress");
    });

    it("Should handle researcher authorization correctly", async function () {
      const { cercleToken, owner, patient1: researcher } = await deployCercleTokenFixture();

      // Initial state
      expect(await cercleToken.authorizedResearchers(researcher.address)).to.be.false;

      // Authorize
      await expect(cercleToken.connect(owner).setAuthorizedResearchers(researcher.address, true))
        .to.emit(cercleToken, "PatientAuthorizationChanged")
        .withArgs(researcher.address, true);

      expect(await cercleToken.authorizedResearchers(researcher.address)).to.be.true;

      // Revoke
      await expect(cercleToken.connect(owner).setAuthorizedResearchers(researcher.address, false))
        .to.emit(cercleToken, "PatientAuthorizationChanged")
        .withArgs(researcher.address, false);

      expect(await cercleToken.authorizedResearchers(researcher.address)).to.be.false;
    });

    it("Should reject zero address for setAuthorizedResearchers", async function () {
      const { cercleToken, owner } = await deployCercleTokenFixture();

      await expect(cercleToken.connect(owner).setAuthorizedResearchers(ethers.ZeroAddress, true))
        .to.be.revertedWithCustomError(cercleToken, "InvalidAddress");
    });
  });

  describe("Data download rewards", function () {
    it("Should allow an authorized researcher to trigger rewards", async function () {
      const { cercleToken, owner, patient1, patient2: researcher, datasetHash } = await deployCercleTokenFixture();

      // Authorize patient (recipient) and researcher (caller)
      await cercleToken.connect(owner).setAuthorizedPatient(patient1.address, true);
      await cercleToken.connect(owner).setAuthorizedResearchers(researcher.address, true);

      await expect(cercleToken.connect(researcher).rewardForDataDownload(patient1.address, datasetHash))
        .to.emit(cercleToken, "DataDownloadRewarded")
        .withArgs(patient1.address, datasetHash, 50);

      expect(await cercleToken.balanceOf(patient1.address)).to.equal(50);
    });

    it("Should reject reward call from an address that is neither patient nor researcher", async function () {
      const { cercleToken, patient1, patient2: stranger, datasetHash } = await deployCercleTokenFixture();

      await expect(cercleToken.connect(stranger).rewardForDataDownload(patient1.address, datasetHash))
        .to.be.revertedWithCustomError(cercleToken, "NotAuthorizedUser");
    });

    it("Should track rewarded datasets in the public mapping", async function () {
      const { cercleToken, patient1, datasetHash } = await deployWithAuthorizedPatients();

      expect(await cercleToken.rewardedDatasets(patient1.address, datasetHash)).to.be.false;

      await cercleToken.connect(patient1).rewardForDataDownload(patient1.address, datasetHash);

      expect(await cercleToken.rewardedDatasets(patient1.address, datasetHash)).to.be.true;
    });

    it("Should reward data downloads correctly", async function () {
      const { cercleToken, patient1, datasetHash } = await deployWithAuthorizedPatients();
      
      const initialBalance = await cercleToken.balanceOf(patient1.address);
      
      await expect(cercleToken.connect(patient1).rewardForDataDownload(patient1.address, datasetHash))
        .and.to.emit(cercleToken, "DataDownloadRewarded")
        .withArgs(patient1.address, datasetHash, 50);
      
      const finalBalance = await cercleToken.balanceOf(patient1.address);
      expect(finalBalance - initialBalance).to.equal(50);
    });

    it("Should restrict minting to authorized patient only", async function () {
      const { cercleToken, patient1, patient2, datasetHash } = await deployCercleTokenFixture();

      await expect(cercleToken.connect(patient1).rewardForDataDownload(patient2.address, datasetHash))
        .to.be.revertedWithCustomError(cercleToken, "NotAuthorizedUser");
    });

    it("Should prevent double-reward for the same dataset hash", async function () {
      const { cercleToken, patient1, datasetHash } = await deployWithAuthorizedPatients();

      await cercleToken.connect(patient1).rewardForDataDownload(patient1.address, datasetHash);

      await expect(cercleToken.connect(patient1).rewardForDataDownload(patient1.address, datasetHash))
        .to.be.revertedWithCustomError(cercleToken, "AlreadyRewarded")
        .withArgs(patient1.address, datasetHash);

      expect(await cercleToken.balanceOf(patient1.address)).to.equal(50);
    });

    it("Should allow reward for different dataset hashes", async function () {
      const { cercleToken, patient1, datasetHash } = await deployWithAuthorizedPatients();
      const datasetHash2 = ethers.keccak256(ethers.toUtf8Bytes("PatientData2"));

      await cercleToken.connect(patient1).rewardForDataDownload(patient1.address, datasetHash);
      await cercleToken.connect(patient1).rewardForDataDownload(patient1.address, datasetHash2);

      expect(await cercleToken.balanceOf(patient1.address)).to.equal(100);
    });

    it("Should allow two patients to be rewarded for the same dataset hash independently", async function () {
      const { cercleToken, patient1, patient2, datasetHash } = await deployWithAuthorizedPatients();

      await cercleToken.connect(patient1).rewardForDataDownload(patient1.address, datasetHash);
      await cercleToken.connect(patient2).rewardForDataDownload(patient2.address, datasetHash);

      expect(await cercleToken.balanceOf(patient1.address)).to.equal(50);
      expect(await cercleToken.balanceOf(patient2.address)).to.equal(50);
    });
  });

  describe("Soul Bound Token implementation", function () {
    it("Should prevent all transfer operations", async function () {
      const { cercleToken, patient1, patient2 } = await deployAuthorizedPatientsWithTokens(); 
        await expect(cercleToken.connect(patient1).transferFrom(patient1.address, patient2.address, 10))
         .to.be.revertedWithCustomError(cercleToken, "AllowanceDisabled");
        await expect(cercleToken.connect(patient1).transfer(patient2.address, 10))
          .to.be.revertedWithCustomError(cercleToken, "TransfersDisabled");
    });

    it("Should prevent all approval operations", async function () {
      const { cercleToken, patient1, patient2 } = await deployAuthorizedPatientsWithTokens();
      await expect(cercleToken.connect(patient1).approve(patient2.address, 10))
        .to.be.revertedWithCustomError(cercleToken, "ApprovalsDisabled");
      await expect(cercleToken.connect(patient1).allowance(patient1.address, patient2.address))
        .to.be.revertedWithCustomError(cercleToken, "AllowanceDisabled");
    });
  });

  describe("Edge cases and error handling", function () {
    it("Should handle multiple patients", async function () {
      const { cercleToken, patient1, patient2, datasetHash } = await deployWithAuthorizedPatients();
      
      // Mint multiple times for patient1 with distinct dataset hashes
      for (let i = 0; i < 4; i++) {
        const hash = ethers.keccak256(ethers.toUtf8Bytes(`PatientData_${i}`));
        await expect(cercleToken.connect(patient1).rewardForDataDownload(patient1.address, hash))
          .to.emit(cercleToken, "DataDownloadRewarded");
      }
      
      // patient2 should still be able to mint
      await expect(cercleToken.connect(patient2).rewardForDataDownload(patient2.address, datasetHash))
        .to.emit(cercleToken, "DataDownloadRewarded");
      
      expect(await cercleToken.balanceOf(patient1.address)).to.equal(200);
      expect(await cercleToken.balanceOf(patient2.address)).to.equal(50);
    });

    it("Should handle authorization revocation", async function () {
      const { cercleToken, owner, patient1, datasetHash } = await deployWithAuthorizedPatients();
      
      // Revoke authorization
      await cercleToken.connect(owner).setAuthorizedPatient(patient1.address, false);
      
      // Should no longer be able to mint
      await expect(cercleToken.connect(patient1).rewardForDataDownload(patient1.address, datasetHash))
        .to.be.revertedWithCustomError(cercleToken, "NotAuthorizedUser");
    });
  });
});