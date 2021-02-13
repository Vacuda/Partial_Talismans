// Copyright 2020 Vacuda


#include "Piece.h"
#include "Talismans/Structs/FTable_Address.h"				// for FTable_Address

// Sets default values
APiece::APiece()
{
 	

}


bool APiece::IsAtHome()
{
    if (Table_Address.PuzzleLetter != HomeTable_Address.PuzzleLetter) {
        UE_LOG(LogTemp, Warning, TEXT(" Puz FALSE"))
        return false;
    }
    if (Table_Address.Board != HomeTable_Address.Board) {
        UE_LOG(LogTemp, Warning, TEXT(" Grid FALSE"))
        return false;
    }
    if (Table_Address.Col != HomeTable_Address.Col) {
        UE_LOG(LogTemp, Warning, TEXT(" Col FALSE"))
        return false;
    }
    if (Table_Address.Row != HomeTable_Address.Row) {
        UE_LOG(LogTemp, Warning, TEXT(" Row FALSE"))
        return false;
    }
    if (Table_Address.Tri != HomeTable_Address.Tri) {
        UE_LOG(LogTemp, Warning, TEXT(" Tri FALSE"))
        return false;
    }

    //else
    return true;   
}
