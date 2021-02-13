// Copyright 2020 Vacuda


#include "PieceMaker.h"

#include "Talismans/Talismans.h"                                // for AJoinUnitCheck
#include "Talismans/Pieces/Piece.h"                             // for APiece
#include "Talismans/Admin/TheGameInstance.h"                    // for UTheGameInstance
#include "Talismans/Enums/E_PuzzleLetter.h"                     // for PuzzleLetter
#include "Talismans/Enums/E_JoinSite.h"                         // for JoinSite
#include "Talismans/Structs/FPuzzleUnit.h"                      // for FPuzzleUnit
#include "Talismans/Structs/FJoinUnit.h"                        // for JoinUnit
#include "Talismans/Structs/FTable_Address.h"                   // for Table_Address



UPieceMaker::UPieceMaker()
{
    
}

//SETUP

void UPieceMaker::CatchTheGameInstance(UTheGameInstance* _GameInstance)
{
    GameInstance = _GameInstance;
}


//GATHER INFO

int32 UPieceMaker::GetCountOfTris(TEnumAsByte <E_PieceShape> Shape)
{
    if (Shape == TRI1) {
        return 1;
    }
    if (Shape == TRI2) {
        return 2;
    }
    if (Shape == TRI3) {
        return 3;
    }
    if (Shape == TRI4) {
        return 4;
    }
    if (Shape == TRI5) {
        return 5;
    }
    if (Shape == TRI6) {
        return 6;
    }
    //safety check
    return 1;
}

int32 UPieceMaker::GetRandIntBasedOnHexCapacity(int32 HexCapacity)
{
    return FMath::RandRange(1, HexCapacity);
}

TEnumAsByte <E_PieceShape> UPieceMaker::GetShape(int32 RandInt)
{
    switch (RandInt) {
        case 1: return TRI1;
        case 2: return TRI2;
        case 3: return TRI3;
        case 4: return TRI4;
        case 5: return TRI5;
        case 6: return TRI6;
    }

    //shouldn't need
    return TRI1;
}

TEnumAsByte <E_Segment> UPieceMaker::GetSegment(int32 SegmentCount)
{
    if (SegmentCount == 1) {
        return SEG1;
    }
    if (SegmentCount == 2) {
        return SEG2;
    }
    if (SegmentCount == 3) {
        return SEG3;
    }
    if (SegmentCount == 4) {
        return SEG4;
    }
    if (SegmentCount == 5) {
        return SEG5;
    }
    if (SegmentCount == 6) {
        return SEG6;
    }
    //safety
    return SEGNONE;
}


//FIND JOIN UNITS

FJoinUnit UPieceMaker::FindJoinUnit_Low(int32 TriStart, TArray<APiece*> HexArray)
{
    FJoinUnit JoinUnit = FJoinUnit();

    //reset TriStart, if needed
    if (TriStart == 0) {
        TriStart = 6;
    }

    int32 TriRunner = TriStart;

    //starts at 1, iterates positive to get Segment
    int32 SegmentCount = 1;

    //loop atmost six times - safety check
    for (int32 i = 1; i <= 6; i++) {

        //loop HexArray
        for (auto& Piece : HexArray) {

            //match
            if (Piece->HomeTable_Address.Tri == TriRunner) {
                JoinUnit.PiecePtr = Piece;
                JoinUnit.Segment = GetSegment(SegmentCount);
                return JoinUnit;
            }
        }

        //no match at that tri

        //iterate TriRunner
        TriRunner--;

        //reset TriRunner, if needed
        if (TriRunner == 0) {
            TriRunner = 6;
        }

        //iterate SegmentCount
        SegmentCount++;
    }

    //safety
    return JoinUnit;
}

FJoinUnit UPieceMaker::FindJoinUnit_High(int32 TriStart, TArray<APiece*> HexArray)
{
    FJoinUnit JoinUnit = FJoinUnit();

    //always will find the next piece is SEG1
    JoinUnit.Segment = SEG1;

    //reset TriStart, if needed
    if (TriStart > 6) {
        TriStart = TriStart - 6;
    }

    //loop HexArray
    for (auto& Piece : HexArray) {
        //match
        if (Piece->HomeTable_Address.Tri == TriStart) {
            JoinUnit.PiecePtr = Piece;
            return JoinUnit;
        }
    }

    //safety
    return JoinUnit;
}


//CHANGE INFO

void UPieceMaker::PlacePiecesIntoRespectiveContainers()
{

    UE_LOG(LogTemp, Warning, TEXT("Total Pieces: %i"), GameInstance->AllPiecesArr.Num())

    //loop all pieces
    for (APiece* Piece : GameInstance->AllPiecesArr) {

        //condense
        TEnumAsByte <E_PuzzleLetter> PuzzleLetter = Piece->Table_Address.PuzzleLetter;
        FPuzzleUnit& Puzzle = GameInstance->PuzzleMap[PuzzleLetter];
        int32 col = Piece->Table_Address.Col;
        int32 row = Piece->Table_Address.Row;
        int32 tri = Piece->Table_Address.Tri;

        //if GRID
        if (Piece->Table_Address.Board == GRID) {

            //get an iteration count for the amount of tris in shape
            int32 tricount = GetCountOfTris(Piece->Shape);

            //iterate tricount times
            for (int32 i = 1; i <= tricount; i++) {

                //ref variable
                FTriangleUnit& TargetTri = Puzzle.ColMapGrid[col].RowMap[row].TriMap[tri];
                  
                if (i == 1) {
                    TargetTri.bIsOrigin = true; 
                }
                
                TargetTri.bIsFilled = true;
                TargetTri.PiecePtr = Piece;
                TargetTri.Segment = GetSegment(i);

                //iterate tri
                tri++;

                //reset tri if over 6
                if (tri == 7) {
                    tri = 1;
                }
            }
        }

        // if BIN
        if (Piece->Table_Address.Board == BIN) {

            //get an iteration count for the amount of tris in shape
            int32 tricount = GetCountOfTris(Piece->Shape);

            //iterate tricount times
            for (int32 i = 1; i <= tricount; i++) {

                UE_LOG(LogTemp, Warning, TEXT("Col: %i, Row: %i, Tri: %i"), col, row, tri)

                //ref variable
                FTriangleUnit& TargetTri = Puzzle.ColMapBin[col].RowMap[row].TriMap[tri];

                if (i == 1) {
                    TargetTri.bIsOrigin = true;
                }

                TargetTri.bIsFilled = true;
                TargetTri.PiecePtr = Piece;
                TargetTri.Segment = GetSegment(i);

                //iterate tri
                tri++;

                //reset tri if over 6
                if (tri == 7) {
                    tri = 1;
                }
            }
        }
    }
}

void UPieceMaker::PiecesWillStartInBin()
{
    if (GameInstance->DebugSettings.bStartInJunction == true) {
        //loop all pieces
        for (auto& Piece : GameInstance->AllPiecesArr) {
            Piece->Table_Address.PuzzleLetter = pJUNCTION;
            Piece->Table_Address.Board = BIN;
            Piece->ClusterPtr->Table_Address.PuzzleLetter = pJUNCTION;
            Piece->ClusterPtr->Table_Address.Board = BIN;
        }
    }
    else {
        //loop all pieces
        for (auto& Piece : GameInstance->AllPiecesArr) {
            Piece->Table_Address.PuzzleLetter = Piece->HomeTable_Address.PuzzleLetter;
            Piece->Table_Address.Board = BIN;
            Piece->ClusterPtr->Table_Address.PuzzleLetter = Piece->HomeTable_Address.PuzzleLetter;
            Piece->ClusterPtr->Table_Address.Board = BIN;
        }
    }




    RandomizeBinPlacement();
}

void UPieceMaker::PiecesWillStartInGrid()
{
    for (auto& Piece : GameInstance->AllPiecesArr) {

        Piece->Table_Address.PuzzleLetter = Piece->HomeTable_Address.PuzzleLetter;
        Piece->Table_Address.Board = GRID;
        Piece->Table_Address.Col = Piece->HomeTable_Address.Col;
        Piece->Table_Address.Row = Piece->HomeTable_Address.Row;
        Piece->Table_Address.Tri = Piece->HomeTable_Address.Tri;

        Piece->ClusterPtr->Table_Address.PuzzleLetter = Piece->HomeTable_Address.PuzzleLetter;
        Piece->ClusterPtr->Table_Address.Board = GRID;
        Piece->ClusterPtr->Table_Address.Col = Piece->HomeTable_Address.Col;
        Piece->ClusterPtr->Table_Address.Row = Piece->HomeTable_Address.Row;
        Piece->ClusterPtr->Table_Address.Tri = Piece->HomeTable_Address.Tri;
    }
}

void UPieceMaker::PiecesWillStartInVessels()
{
    //initialize AllRoomsArr
    TArray<TEnumAsByte <E_RoomLetter>> AllRoomsArr;

    //make AllRoomsArr
    for (auto& Room : GameInstance->RoomMap) {
        AllRoomsArr.Emplace(Room.Key);
    }

    //loop all pieces
    for (auto& Piece : GameInstance->AllPiecesArr) {

        //initialize trigger
        bool bPiecePlaced = false;

        //start while loop
        while (bPiecePlaced == false) {

            //get random Tot
            int32 RandCol = FMath::RandRange(1, 40);
            int32 RandRow = FMath::RandRange(1, 20);
            int32 RandTot = FMath::RandRange(0, 5);
            int32 RandRoom = FMath::RandRange(0, AllRoomsArr.Num() - 1);

            //condense
            FTotemUnit& Tot = GameInstance->RoomMap[AllRoomsArr[RandRoom]].ColMap[RandCol].RowMap[RandRow].TotMap[RandTot];

            //if Vessel
            if (Tot.TotemType == tVESSEL) {

                //add piece into vessel
                Tot.VesselPiecesArr.Emplace(Piece);

                //change piece room address
                Piece->Room_Address.RoomLetter = AllRoomsArr[RandRoom];
                Piece->Room_Address.Col = RandCol;
                Piece->Room_Address.Row = RandRow;
                Piece->Room_Address.Tot = RandTot;

                //Piece needs a default tri
                Piece->Table_Address.Tri = FMath::RandRange(1, 6);
                Piece->ClusterPtr->Table_Address.Tri = 1;

                //go to next piece
                bPiecePlaced = true;
            }
        }
    }
}

void UPieceMaker::RandomizeBinPlacement()
{
    //@@@@ Too much looping???
    //@@@@ yuck, so ugly

    //loop Puzzles
    for (auto& Puzzle : GameInstance->PuzzleMap) {

        //condense
        TEnumAsByte <E_PuzzleLetter> PuzzleLetter = Puzzle.Key;
        TArray<APiece*>& AllPiecesArr = GameInstance->AllPiecesArr;

        //Determine RowAmount
        int32 RowAmount;
        if (PuzzleLetter == pJUNCTION) {
            RowAmount = 25;
        }
        else {
            RowAmount = 13;
        }

        //indexes of AllPiecesArr that match PuzzleLetter
        TArray<int32> IndexArr;

        //@@@@ I already build this in each PuzzleUnit.  Should just copy TArray

        //loop all pieces, match PuzzleLetter
        for (int32 i = 0; i < AllPiecesArr.Num(); i++) {
            if (AllPiecesArr[i]->Table_Address.PuzzleLetter == PuzzleLetter) {
                //put indexes into IndexArr
                IndexArr.Emplace(i);
            }
        }

        UE_LOG(LogTemp, Warning, TEXT("how many pieces picked: %i"), IndexArr.Num())

        int32 col = 2; //starts at 2, to keep aligned with even column numbers
        int32 row = 1;

        // change Table_Address col and row of pieces
        while (IndexArr.Num() != 0) {
            // get random index/piece
            int32 RandInt = FMath::RandRange(0, IndexArr.Num() - 1);

            //condense
            auto& Piece = AllPiecesArr[IndexArr[RandInt]];

            //piece info
            Piece->Table_Address.Col = col;
            Piece->Table_Address.Row = row;
            Piece->Table_Address.Tri = FMath::RandRange(1, 6);

            //cluster info
            Piece->ClusterPtr->Table_Address.Col = col;
            Piece->ClusterPtr->Table_Address.Row = row;
            Piece->ClusterPtr->Table_Address.Tri = Piece->Table_Address.Tri;

            //iterate row
            row += 2;

            //reset row
            if (row >= RowAmount) {

                //iterate col
                col++;

                //if col odd
                if (col % 2 == 1) {
                    row = 2;
                }
                //if col even
                else {
                    row = 1;
                }
            }

            //this is the iteration for the while loop
            //remove this piece from arr
            IndexArr.RemoveAt(RandInt);

        }
    }
}


//BUILD

//void UPieceMaker::BuildFullSetHexPieces()
//{
//
//    //all tri6
//
//    int32 col = 1;
//    int32 row = 1;
//
//    for (int32 i = 0; i < 21; i++) {
//
//        APiece* OnePiece = NewObject<APiece>(GameInstance, APiece::StaticClass());
//
//        OnePiece->Shape = TRI6;
//        OnePiece->State = ONGRID;
//        OnePiece->Table_Address.Col = col;
//        OnePiece->Table_Address.Row = row;
//        OnePiece->Table_Address.Tri = FMath::RandRange(1, 6);
//        OnePiece->Table_Address.Board = GRID;
//
//        GameInstance->AllPiecesArr.Emplace(OnePiece);
//
//        row++;
//
//        if (row == 4) {
//            row = 1;
//            col = col++;
//        }
//
//    }
//
//
//    //all tri1
//    //int32 col = 1;
//    //int32 row = 1;
//    //int32 tri = 1;
//
//    //for (int32 i = 0; i < 126; i++) {
//
//    //    APiece* OnePiece = NewObject<APiece>(GameInstance, APiece::StaticClass());
//
//    //    OnePiece->Shape = TRI1;
//    //    OnePiece->State = ONGRID;
//    //    OnePiece->Table_Address.Col = col;
//    //    OnePiece->Table_Address.Row = row;
//    //    OnePiece->Table_Address.Tri = tri;
//    //    OnePiece->Table_Address.Board = GRID;
//
//    //    Hub->GameInstance->AllPiecesArr.Emplace(OnePiece);
//
//    //    tri++;
//
//    //    if (tri == 7) {
//    //        tri = 1;
//    //        row++;
//    //    }
//
//    //    if (row == 4) {
//    //        row = 1;
//    //        col++;
//    //    }
//    //}
//
//
//
//
//
//
//
//
//    PlacePiecesIntoRespectiveContainers();
//}

void UPieceMaker::BuildFullAndRandomlyCutPieces()
{
    //condense
    TMap<TEnumAsByte <E_PuzzleLetter>, FPuzzleUnit>& PuzzleMap = GameInstance->PuzzleMap;

    for (auto& Puzzle : PuzzleMap) {

        //skip pJUNCTION
        if (Puzzle.Key == pJUNCTION) {
            continue;
        }

        //UE_LOG(LogTemp, Warning, TEXT("Puzzle, should be 13 of these +1...."))

        int32 HexCapacity = 6;
        int32 colsize = Puzzle.Value.PuzzleGridWidth; 
        int32 rowsize = Puzzle.Value.PuzzleGridHeight;
        int32 col = 1;
        int32 row = 2;  //odd colums start at 2
        int32 tri = 1;

        //@@@@ Need to figure out how to start with a random tri

        //calculate iteration of puzzle spaces
        int32 FullGridIteration = colsize * rowsize * 6;
    
        //iterate through full grid size
        for (int32 i = 0; i < FullGridIteration; /* No iteration here*/  ) {

            //UE_LOG(LogTemp, Warning, TEXT("col: %i, row: %i, tri: %i"), col, row, tri)

            //make new piece
            APiece* OnePiece = NewObject<APiece>(GameInstance, APiece::StaticClass());

            //get rand number based on open spaces of the current Hex
            int32 RandInt = GetRandIntBasedOnHexCapacity(HexCapacity);

            //UE_LOG(LogTemp, Warning, TEXT("RandInt: %i"), RandInt)
                //UE_LOG(LogTemp, Warning, TEXT("---"))

            OnePiece->Shape = GetShape(RandInt);
            OnePiece->State = ONGRID;

            // Home Table_Address
            OnePiece->HomeTable_Address.PuzzleLetter = Puzzle.Key;
            OnePiece->HomeTable_Address.Col = col;
            OnePiece->HomeTable_Address.Row = row;
            OnePiece->HomeTable_Address.Tri = tri;
            OnePiece->HomeTable_Address.Board = GRID;

            //add ptr to all Array
            GameInstance->AllPiecesArr.Emplace(OnePiece);

            //add ptr to puzzle array
            Puzzle.Value.HomePiecesArray.Emplace(OnePiece);

            //adds randint to tri, to keep proper tri value
            tri += RandInt;

            //decrease space in HexCapacity by the newly created shape
            HexCapacity -= RandInt;

            //reset HexCapacity when full
            if (HexCapacity <= 0) {
                HexCapacity = 6;
            }

            //iterate i according to piece made
            i += RandInt;

            //reset tri, iterate row
            if (tri == 7) {
                tri = 1;
                row += 2;
            }

            //reset row
            if (row >= 7) {

                //iterate col
                col++;

                //if col odd
                if (col % 2 == 1) {
                    row = 2;
                }
                //if col even
                else {
                    row = 1;
                }
            }
        }
    }
}

void UPieceMaker::CreateClusters()
{

    for (auto& Piece : GameInstance->AllPiecesArr) {

        //make new cluster
        ACluster* NewCluster = NewObject<ACluster>(GameInstance, ACluster::StaticClass());

        //link piece to cluster
        Piece->ClusterPtr = NewCluster;
        
        //set cluster info
        NewCluster->Table_Address = Piece->Table_Address;
        NewCluster->State = Piece->State;

        //link cluster to piece
        NewCluster->HeldPieces.Emplace(Piece);

        //store cluster
        GameInstance->AllClustersArr.Emplace(NewCluster);

    }

    UE_LOG(LogTemp, Warning, TEXT("Amount of clusters: %i"), GameInstance->AllClustersArr.Num())
}

void UPieceMaker::FillJoinMaps()
{
    //loop pieces
    for (auto& Piece : GameInstance->AllPiecesArr) {

        //condense
        TEnumAsByte <E_PuzzleLetter> PuzzleLetter = Piece->HomeTable_Address.PuzzleLetter;
        FPuzzleUnit& Puzzle = GameInstance->PuzzleMap[PuzzleLetter];
        int32 Col = Piece->HomeTable_Address.Col;
        int32 Row = Piece->HomeTable_Address.Row;
        int32 Tri = Piece->HomeTable_Address.Tri;

        int32 tricount = GetCountOfTris(Piece->Shape);

        //items to fill
        TArray<APiece*> ThisHexArray;
        TArray<APiece*> UpHexArray;
        TArray<APiece*> UpLeftHexArray;
        TArray<APiece*> UpRightHexArray;
        TArray<APiece*> DownHexArray;
        TArray<APiece*> DownLeftHexArray;
        TArray<APiece*> DownRightHexArray;

        //loop pieces that are part of this puzzle
        for (auto& OtherPiece : Puzzle.HomePiecesArray) {

            //EXIT EARLY
            if (OtherPiece->HomeTable_Address.Col < Col - 1) {
                continue;
            }
            //EXIT EARLY
            if (OtherPiece->HomeTable_Address.Col > Col + 1) {
                continue;
            }

            //left of center
            if (OtherPiece->HomeTable_Address.Col == Col - 1) {

                //upleft
                if (OtherPiece->HomeTable_Address.Row == Row - 1) {
                    UpLeftHexArray.Emplace(OtherPiece);
                }

                //downleft
                if (OtherPiece->HomeTable_Address.Row == Row + 1) {
                    DownLeftHexArray.Emplace(OtherPiece);
                }
            }

            //center
            if (OtherPiece->HomeTable_Address.Col == Col) {

                //up
                if (OtherPiece->HomeTable_Address.Row == Row - 2) {
                    UpHexArray.Emplace(OtherPiece);
                }

                //center
                if (OtherPiece->HomeTable_Address.Row == Row) {
                    //not your piece
                    if (OtherPiece->HomeTable_Address.Tri != Tri) {
                        ThisHexArray.Emplace(OtherPiece);
                    }
                }

                //down
                if (OtherPiece->HomeTable_Address.Row == Row + 2) {
                    DownHexArray.Emplace(OtherPiece);
                }
            }

            //right of center
            if (OtherPiece->HomeTable_Address.Col == Col + 1) {

                //upright
                if (OtherPiece->HomeTable_Address.Row == Row - 1) {
                    UpRightHexArray.Emplace(OtherPiece);
                }

                //downright
                if (OtherPiece->HomeTable_Address.Row == Row + 1) {
                    DownRightHexArray.Emplace(OtherPiece);
                }
            }
        }

        //DEBUG
        /*if (PuzzleLetter == p001) {

            if (Piece->HomeTable_Address.Col == 1) {
                UE_LOG(AJoinUnitCheck, Display, TEXT("&&&&&&&&11111&&&&&&&"))
                UE_LOG(AJoinUnitCheck, Display, TEXT("ThisHexArray: %i"), ThisHexArray.Num())
                UE_LOG(AJoinUnitCheck, Display, TEXT("UpHexArray: %i"), UpHexArray.Num())
                UE_LOG(AJoinUnitCheck, Display, TEXT("UpLeftHexArray: %i"), UpLeftHexArray.Num())
                UE_LOG(AJoinUnitCheck, Display, TEXT("UpRightArray: %i"), UpRightHexArray.Num())
                UE_LOG(AJoinUnitCheck, Display, TEXT("DownHexArray: %i"), DownHexArray.Num())
                UE_LOG(AJoinUnitCheck, Display, TEXT("DownLeftHexArray: %i"), DownLeftHexArray.Num())
                UE_LOG(AJoinUnitCheck, Display, TEXT("DownRightHexArray: %i"), DownRightHexArray.Num())
            }

            if (Piece->HomeTable_Address.Col == 3) {
                UE_LOG(AJoinUnitCheck, Display, TEXT("&&&&&&&&22222&&&&&&&"))
                UE_LOG(AJoinUnitCheck, Display, TEXT("ThisHexArray: %i"), ThisHexArray.Num())
                UE_LOG(AJoinUnitCheck, Display, TEXT("UpHexArray: %i"), UpHexArray.Num())
                UE_LOG(AJoinUnitCheck, Display, TEXT("UpLeftHexArray: %i"), UpLeftHexArray.Num())
                UE_LOG(AJoinUnitCheck, Display, TEXT("UpRightArray: %i"), UpRightHexArray.Num())
                UE_LOG(AJoinUnitCheck, Display, TEXT("DownHexArray: %i"), DownHexArray.Num())
                UE_LOG(AJoinUnitCheck, Display, TEXT("DownLeftHexArray: %i"), DownLeftHexArray.Num())
                UE_LOG(AJoinUnitCheck, Display, TEXT("DownRightHexArray: %i"), DownRightHexArray.Num())

            }

            if (Piece->HomeTable_Address.Col == 7) {
                UE_LOG(AJoinUnitCheck, Display, TEXT("&&&&&&&333333&&&&&&&&&"))
                UE_LOG(AJoinUnitCheck, Display, TEXT("ThisHexArray: %i"), ThisHexArray.Num())
                UE_LOG(AJoinUnitCheck, Display, TEXT("UpHexArray: %i"), UpHexArray.Num())
                UE_LOG(AJoinUnitCheck, Display, TEXT("UpLeftHexArray: %i"), UpLeftHexArray.Num())
                UE_LOG(AJoinUnitCheck, Display, TEXT("UpRightArray: %i"), UpRightHexArray.Num())
                UE_LOG(AJoinUnitCheck, Display, TEXT("DownHexArray: %i"), DownHexArray.Num())
                UE_LOG(AJoinUnitCheck, Display, TEXT("DownLeftHexArray: %i"), DownLeftHexArray.Num())
                UE_LOG(AJoinUnitCheck, Display, TEXT("DownRightHexArray: %i"), DownRightHexArray.Num())
            }
        }*/

//ARRAYS BUILT

    //FIND ALL JOINUNITS

        FJoinUnit UpUnit = FJoinUnit();
        FJoinUnit UpLeftUnit = FJoinUnit();
        FJoinUnit UpRightUnit = FJoinUnit();
        FJoinUnit DownUnit = FJoinUnit();
        FJoinUnit DownLeftUnit = FJoinUnit();
        FJoinUnit DownRightUnit = FJoinUnit();

        //UpUnit
        if (UpHexArray.Num() != 0) {

            //start info
            int32 TriRunner = 1;
            int32 SegmentCount = 1;

            while (!UpUnit.PiecePtr) {

                //loop UpHexArray
                for (auto& PossiblePiece : UpHexArray) {

                    //match
                    if (PossiblePiece->HomeTable_Address.Tri == TriRunner) {
                        
                        UpUnit.PiecePtr = PossiblePiece;
                        UpUnit.Segment = GetSegment(SegmentCount);
                        break;
                    }
                }
                //if no match

                //iterate TriRunner
                TriRunner--;

                //reset TriRunner, if needed
                if (TriRunner == 0) {
                    TriRunner = 6;
                }

                //iterate SegmentCount
                SegmentCount++;
            }
        }

        //UpLeftUnit
        if (UpLeftHexArray.Num() != 0) {

            //start info
            int32 TriRunner = 2;
            int32 SegmentCount = 1;

            while (!UpLeftUnit.PiecePtr) {

                //loop UpLeftHexArray
                for (auto& PossiblePiece : UpLeftHexArray) {

                    //match
                    if (PossiblePiece->HomeTable_Address.Tri == TriRunner) {
                        UpLeftUnit.PiecePtr = PossiblePiece;
                        UpLeftUnit.Segment = GetSegment(SegmentCount);
                        break;
                    }
                }
                //if no match

                //iterate TriRunner
                TriRunner--;

                //reset TriRunner, if needed
                if (TriRunner == 0) {
                    TriRunner = 6;
                }

                //iterate SegmentCount
                SegmentCount++;
            }
        }

        //UpRightUnit
        if (UpRightHexArray.Num() != 0) {

            //start info
            int32 TriRunner = 6;
            int32 SegmentCount = 1;


            while (!UpRightUnit.PiecePtr) {

                //loop UpRightHexArray
                for (auto& PossiblePiece : UpRightHexArray) {

                    //match
                    if (PossiblePiece->HomeTable_Address.Tri == TriRunner) {
                        UpRightUnit.PiecePtr = PossiblePiece;
                        UpRightUnit.Segment = GetSegment(SegmentCount);
                        break;
                    }
                }
                //if no match

                //iterate TriRunner
                TriRunner--;

                //reset TriRunner, if needed
                if (TriRunner == 0) {
                    TriRunner = 6;
                }

                //iterate SegmentCount
                SegmentCount++;
            }
        }

        //DownUnit
        if (DownHexArray.Num() != 0) {

            //start info
            int32 TriRunner = 4;
            int32 SegmentCount = 1;


            while (!DownUnit.PiecePtr) {

                //loop DownHexArray
                for (auto& PossiblePiece : DownHexArray) {

                    //match
                    if (PossiblePiece->HomeTable_Address.Tri == TriRunner) {
                        DownUnit.PiecePtr = PossiblePiece;
                        DownUnit.Segment = GetSegment(SegmentCount);
                        break;
                    }
                }
                //if no match

                //iterate TriRunner
                TriRunner--;

                //reset TriRunner, if needed
                if (TriRunner == 0) {
                    TriRunner = 6;
                }

                //iterate SegmentCount
                SegmentCount++;
            }
        }

        //DownLeftUnit
        if (DownLeftHexArray.Num() != 0) {

            //start info
            int32 TriRunner = 3;
            int32 SegmentCount = 1;

            while (!DownLeftUnit.PiecePtr) {

                //loop DownLeftHexArray
                for (auto& PossiblePiece : DownLeftHexArray) {

                    //match
                    if (PossiblePiece->HomeTable_Address.Tri == TriRunner) {
                        DownLeftUnit.PiecePtr = PossiblePiece;
                        DownLeftUnit.Segment = GetSegment(SegmentCount);
                        break;
                    }
                }
                //if no match

                //iterate TriRunner
                TriRunner--;

                //reset TriRunner, if needed
                if (TriRunner == 0) {
                    TriRunner = 6;
                }

                //iterate SegmentCount
                SegmentCount++;
            }
        }

        //DownRightUnit
        if (DownRightHexArray.Num() != 0) {

            //start info
            int32 TriRunner = 5;
            int32 SegmentCount = 1;

            while (!DownRightUnit.PiecePtr) {

                //loop DownRightHexArray
                for (auto& PossiblePiece : DownRightHexArray) {

                    //match
                    if (PossiblePiece->HomeTable_Address.Tri == TriRunner) {
                        DownRightUnit.PiecePtr = PossiblePiece;
                        DownRightUnit.Segment = GetSegment(SegmentCount);
                        break;
                    }
                }
                //if no match

                //iterate TriRunner
                TriRunner--;

                //reset TriRunner, if needed
                if (TriRunner == 0) {
                    TriRunner = 6;
                }

                //iterate SegmentCount
                SegmentCount++;
            }
        }

    //FIND jLOW and jHIGH

        //if not TRI6, Low and High will be found
        if (Piece->Shape != TRI6) {

            //find jLOW
            FJoinUnit LowUnit = FindJoinUnit_Low(Tri - 1, ThisHexArray);
            //find jHIGH
            FJoinUnit HighUnit = FindJoinUnit_High(Tri + tricount, ThisHexArray);

            //doubles check
            if (LowUnit.PiecePtr == HighUnit.PiecePtr) {
                Piece->JoinMap.Emplace(jLOW, LowUnit);
            }
            else {
                Piece->JoinMap.Emplace(jLOW, LowUnit);
                Piece->JoinMap.Emplace(jHIGH, HighUnit);
            }
        }

    // FIND TRIs

        //find jTRI1
        if (Piece->Shape == TRI1 ||
            Piece->Shape == TRI2 ||
            Piece->Shape == TRI3 ||
            Piece->Shape == TRI4 ||
            Piece->Shape == TRI5 ||
            Piece->Shape == TRI6 ) {
            
            if (Tri == 1) {
                if (DownUnit.PiecePtr) {
                    Piece->JoinMap.Emplace(jTRI1, DownUnit);
                }
            }
            if (Tri == 2) {
                if (DownRightUnit.PiecePtr) {
                    Piece->JoinMap.Emplace(jTRI1, DownRightUnit);
                }
            }
            if (Tri == 3) {
                if (UpRightUnit.PiecePtr) {
                    Piece->JoinMap.Emplace(jTRI1, UpRightUnit);
                }
            }
            if (Tri == 4) {
                if (UpUnit.PiecePtr) {
                    Piece->JoinMap.Emplace(jTRI1, UpUnit);
                }
            }
            if (Tri == 5) {
                if (UpLeftUnit.PiecePtr) {
                    Piece->JoinMap.Emplace(jTRI1, UpLeftUnit);
                }
            }
            if (Tri == 6) {
                if (DownLeftUnit.PiecePtr) {
                    Piece->JoinMap.Emplace(jTRI1, DownLeftUnit);
                }
            }
        }

        //find jTRI2
        if (Piece->Shape == TRI2 ||
            Piece->Shape == TRI3 ||
            Piece->Shape == TRI4 ||
            Piece->Shape == TRI5 ||
            Piece->Shape == TRI6) {

            if (Tri == 1) {
                if (DownRightUnit.PiecePtr) {
                    Piece->JoinMap.Emplace(jTRI2, DownRightUnit);
                }
            }
            if (Tri == 2) {
                if (UpRightUnit.PiecePtr) {
                    Piece->JoinMap.Emplace(jTRI2, UpRightUnit);
                }
            }
            if (Tri == 3) {
                if (UpUnit.PiecePtr) {
                    Piece->JoinMap.Emplace(jTRI2, UpUnit);
                }
            }
            if (Tri == 4) {
                if (UpLeftUnit.PiecePtr) {
                    Piece->JoinMap.Emplace(jTRI2, UpLeftUnit);
                }
            }
            if (Tri == 5) {
                if (DownLeftUnit.PiecePtr) {
                    Piece->JoinMap.Emplace(jTRI2, DownLeftUnit);
                }
            }
            if (Tri == 6) {
                if (DownUnit.PiecePtr) {
                    Piece->JoinMap.Emplace(jTRI2, DownUnit);
                }
            }
        }

        //find jTRI3
        if (Piece->Shape == TRI3 ||
            Piece->Shape == TRI4 ||
            Piece->Shape == TRI5 ||
            Piece->Shape == TRI6) {

            if (Tri == 1) {
                if (UpRightUnit.PiecePtr) {
                    Piece->JoinMap.Emplace(jTRI3, UpRightUnit);
                }
            }
            if (Tri == 2) {
                if (UpUnit.PiecePtr) {
                    Piece->JoinMap.Emplace(jTRI3, UpUnit);
                }
            }
            if (Tri == 3) {
                if (UpLeftUnit.PiecePtr) {
                    Piece->JoinMap.Emplace(jTRI3, UpLeftUnit);
                }
            }
            if (Tri == 4) {
                if (DownLeftUnit.PiecePtr) {
                    Piece->JoinMap.Emplace(jTRI3, DownLeftUnit);
                }
            }
            if (Tri == 5) {
                if (DownUnit.PiecePtr) {
                    Piece->JoinMap.Emplace(jTRI3, DownUnit);
                }
            }
            if (Tri == 6) {
                if (DownRightUnit.PiecePtr) {
                    Piece->JoinMap.Emplace(jTRI3, DownRightUnit);
                }
            }
        }

        //find jTRI4
        if (Piece->Shape == TRI4 ||
            Piece->Shape == TRI5 ||
            Piece->Shape == TRI6) {

            if (Tri == 1) {
                if (UpUnit.PiecePtr) {
                    Piece->JoinMap.Emplace(jTRI4, UpUnit);
                }
            }
            if (Tri == 2) {
                if (UpLeftUnit.PiecePtr) {
                    Piece->JoinMap.Emplace(jTRI4, UpLeftUnit);
                }
            }
            if (Tri == 3) {
                if (DownLeftUnit.PiecePtr) {
                    Piece->JoinMap.Emplace(jTRI4, DownLeftUnit);
                }
            }
            if (Tri == 4) {
                if (DownUnit.PiecePtr) {
                    Piece->JoinMap.Emplace(jTRI4, DownUnit);
                }
            }
            if (Tri == 5) {
                if (DownRightUnit.PiecePtr) {
                    Piece->JoinMap.Emplace(jTRI4, DownRightUnit);
                }
            }
            if (Tri == 6) {
                if (UpRightUnit.PiecePtr) {
                    Piece->JoinMap.Emplace(jTRI4, UpRightUnit);
                }
            }
        }

        //find jTRI5
        if (Piece->Shape == TRI5 ||
            Piece->Shape == TRI6) {

            if (Tri == 1) {
                if (UpLeftUnit.PiecePtr) {
                    Piece->JoinMap.Emplace(jTRI5, UpLeftUnit);
                }
            }
            if (Tri == 2) {
                if (DownLeftUnit.PiecePtr) {
                    Piece->JoinMap.Emplace(jTRI5, DownLeftUnit);
                }
            }
            if (Tri == 3) {
                if (DownUnit.PiecePtr) {
                    Piece->JoinMap.Emplace(jTRI5, DownUnit);
                }
            }
            if (Tri == 4) {
                if (DownRightUnit.PiecePtr) {
                    Piece->JoinMap.Emplace(jTRI5, DownRightUnit);
                }
            }
            if (Tri == 5) {
                if (UpRightUnit.PiecePtr) {
                    Piece->JoinMap.Emplace(jTRI5, UpRightUnit);
                }
            }
            if (Tri == 6) {
                if (UpUnit.PiecePtr) {
                    Piece->JoinMap.Emplace(jTRI5, UpUnit);
                }
            }
        }

        //find jTRI6
        if (Piece->Shape == TRI6) {

            if (Tri == 1) {
                if (DownLeftUnit.PiecePtr) {
                    Piece->JoinMap.Emplace(jTRI6, DownLeftUnit);  
                }
            }
            if (Tri == 2) {
                if (DownUnit.PiecePtr) {
                    Piece->JoinMap.Emplace(jTRI6, DownUnit);
                }
            }
            if (Tri == 3) {
                if (DownRightUnit.PiecePtr) {
                    Piece->JoinMap.Emplace(jTRI6, DownRightUnit);
                }
            }
            if (Tri == 4) {
                if (UpRightUnit.PiecePtr) {
                    Piece->JoinMap.Emplace(jTRI6, UpRightUnit);
                }
            }
            if (Tri == 5) {
                if (UpUnit.PiecePtr) {
                    Piece->JoinMap.Emplace(jTRI6, UpUnit);
                }
            }
            if (Tri == 6) {
                if (UpLeftUnit.PiecePtr) {
                    Piece->JoinMap.Emplace(jTRI6, UpLeftUnit);
                }
            }
        }

        //DEBUG
        if (PuzzleLetter == p001) {

            const TEnumAsByte<E_PieceShape> Shape = Piece->Shape; 
            FString ShapeString = UEnum::GetValueAsString(Shape.GetValue());



            UE_LOG(AJoinUnitCheck, Display, TEXT("@@@@@@@@@@@@@@@@@@@@@@@@"))
            UE_LOG(AJoinUnitCheck, Display, TEXT("Shape: %s"), *ShapeString)

            for (auto& Join : Piece->JoinMap) {

                const TEnumAsByte<E_JoinSite> JoinSite = Join.Key;
                FString JoinSiteString = UEnum::GetValueAsString(JoinSite.GetValue());

                UE_LOG(AJoinUnitCheck, Display, TEXT("JoinMap: %s"), *JoinSiteString)


                const TEnumAsByte<E_Segment> Seg = Join.Value.Segment;
                FString SegString = UEnum::GetValueAsString(Seg.GetValue());

                UE_LOG(AJoinUnitCheck, Display, TEXT("----Seg: %s"), *SegString)

            }

            UE_LOG(AJoinUnitCheck, Display, TEXT("@@@@@@@@@@@@@@@@@@@@@@@@"))

        }
    }
}






