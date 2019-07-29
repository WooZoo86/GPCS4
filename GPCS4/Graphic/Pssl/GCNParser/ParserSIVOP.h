//=============================================================
// Copyright (c) 2013 Advanced Micro Devices, Inc.
//=============================================================

#ifndef __PARSESIVOP_H
#define __PARSESIVOP_H

#include "ParserSI.h"

/// -----------------------------------------------------------------------------------------------
/// \class Name: ParserSIVOP : public ParserSI { };
/// \brief Description:  Parser for the Southern Island [SI] VOP instructions
/// -----------------------------------------------------------------------------------------------
class ParserSIVOP : public ParserSI
{
public:
    /// -----------------------------------------------------------------------------------------------
    /// \brief Name:        Parse
    /// \brief Description: Parse the 32-bit VOP instruction (Suits VOP1,VOP2,VOPC)
    /// \param[in]          hexInstruction
    /// \param[in]          instruction
    /// \param[in]          isLiteral32b
    /// \param[in]          literal32b
    /// \return ParserSI::Status
    /// -----------------------------------------------------------------------------------------------
    ParserSI::kaStatus Parse32(GDT_HW_GENERATION hwGen, Instruction::instruction32bit hexInstruction, Instruction*& instruction);
    /// -----------------------------------------------------------------------------------------------
    /// \brief Name:        Parse
    /// \brief Description: Parse the 64-bit VOP instruction (Suits 2 kinds of VOP3)
    /// \param[in]          hexInstruction
    /// \param[in]          instruction
    /// \return ParserSI::Status
    /// -----------------------------------------------------------------------------------------------
    ParserSI::kaStatus Parse64(GDT_HW_GENERATION hwGen, Instruction::instruction64bit hexInstruction, Instruction*& instruction);
    /// -----------------------------------------------------------------------------------------------
    /// \brief Name:        ParserSIVOP
    /// \brief Description: ctor
    /// \return
    /// -----------------------------------------------------------------------------------------------
    ParserSIVOP() { }
    /// -----------------------------------------------------------------------------------------------
    /// \brief Name:        ~ParserSIVOP
    /// \brief Description: dtor
    /// \return
    /// -----------------------------------------------------------------------------------------------
    ~ParserSIVOP() { }
private:

	/// VOP3 Instruction`s fields masks
	enum VOPMask : uint32_t
	{
		///    SRC0 [8:0]
		VOPMask_SRC0 = 0x000001FF,
		///    VSRC1 [16:9]
		VOPMask_VSRC1 = 0x000000FF << 9,

		///    VDST [24:17]
		VOP1Mask_VDST = 0x000000FF << 17,


		///    VDST [24:17]
		VOP2Mask_VDST = 0x000000FF << 17,

	};

	enum VOP3Mask : uint64_t
	{
		///    SRC1 [17:9]
		VOP3Mask_SRC1 = 0x00000000000001FF << 9,
		///    SRC2 [26:18]
		VOP3Mask_SRC2 = 0x00000000000001FF << 18,
		///    OMOD [28:27]
		VOP3Mask_OMOD = 0x0000000000000003 << 27,
		///    NEG [31:29]
		VOP3Mask_NEG = 0x0000000000000007 << 29,
		///    VDST [39:32]
		VOP3Mask_VDST = 0x00000000000000FF << 32,
		///    SDST [46:40]
		VOP3Mask_SDST = 0x000000000000007F << 40,
		///    ABS [42:40]
		VOP3Mask_ABS = 0x0000000000000007 << 40,
		///    CLMP [43]
		VOP3Mask_CLMP = 0x0000000000000001 << 43,
	};
    //
    // Private member functions
    //

	static VOPInstruction::SRC GetSRC(Instruction::instruction64bit hexInstruction, unsigned int& ridx, unsigned int idxSRC);

	static VOPInstruction::VSRC GetVSRC1(Instruction::instruction64bit hexInstruction, unsigned int& ridx);

	static VOPInstruction::VDST GetVDST(Instruction::instruction64bit hexInstruction, unsigned int& ridx, VOPInstruction::Encoding enc);

	static VOPInstruction::SDST GetSDST(Instruction::instruction64bit hexInstruction, unsigned int& ridx);

	static VOPInstruction::OMOD GetOMOD(Instruction::instruction64bit hexInstruction);

	static VOPInstruction::NEG GetNEG(Instruction::instruction64bit hexInstruction);

	static VOPInstruction::ABS GetABS(Instruction::instruction64bit hexInstruction);

	static VOPInstruction::CLMP GetCLMP(Instruction::instruction64bit hexInstruction);

    /// -----------------------------------------------------------------------------------------------
    /// \brief Name:        GetInstructionType
    /// \brief Description: Get VOP Instruction type
    /// \param[in]          hexInstruction
    /// \return VOPInstruction::InstructionType
    /// -----------------------------------------------------------------------------------------------
    static VOPInstruction::Encoding GetInstructionType(Instruction::instruction32bit hexInstruction);
    /// -----------------------------------------------------------------------------------------------
    /// \brief Name:        GetInstructionType
    /// \brief Description: Get VOP Instruction type
    /// \param[in]          hexInstruction
    /// \return VOPInstruction::InstructionType
    /// -----------------------------------------------------------------------------------------------
    static VOPInstruction::Encoding GetInstructionType(Instruction::instruction64bit hexInstruction);

};

#endif //__PARSESIVOP_H
