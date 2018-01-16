#include "variables.h"

void GenerateBoard( gameV * );

int CheckState( gameV * );

void PutPenguin( gameV *, coordinates );

void NextPlayer( gameV * );

void TakePenguin( gameV *, coordinates );

char CheckMoves( gameV *, coordinates );

int CheckIfMovePossible( gameV *, coordinates );
