///////////////////////////////////////////////////////////////////////////
//calulate where color locate
void findAim() {
  for (int forRow = 0; forRow < aimRows; forRow ++) {
    for (int forColumn = 0; forColumn < aimColumns; forColumn ++) {
      if (aimArray[forRow][forColumn] == 'r') {
        aimInfo2[0] = forRow;
        aimInfo2[1] = forColumn;
        aimInfo[0] = 'r';
        myRow = forRow;
        myColumn = forColumn;
        return;
      } else if (aimArray[forRow][forColumn] == 'y') {
        aimInfo2[0] = forRow;
        aimInfo2[1] = forColumn;
        aimInfo[0] = 'y';
        myRow = forRow;
        myColumn = forColumn;
        return;
      } else if (aimArray[forRow][forColumn] == 'g') {
        aimInfo2[0] = forRow;
        aimInfo2[1] = forColumn;
        aimInfo[0] = 'g';
        myRow = forRow;
        myColumn = forColumn;
        return;
      } else if (aimArray[forRow][forColumn] == 'b') {
        aimInfo2[0] = forRow;
        aimInfo2[1] = forColumn;
        aimInfo[0] = 'b';
        myRow = forRow;
        myColumn = forColumn;
        return;
      }
    }
  }
}

void findObject() {
  for (int currentRow = 0; currentRow < objectRows; currentRow ++) {
    for (int currentColumn = 0; currentColumn < objectColumns; currentColumn ++) {
      if (objectArray[currentRow][currentColumn] == 'r') {
        redInfo[0] = currentRow;
        redInfo[1] = currentColumn;
      } else if (objectArray[currentRow][currentColumn] == 'y') {
        yelloInfo[0] = currentRow;
        yelloInfo[1] = currentColumn;
      } else if (objectArray[currentRow][currentColumn] == 'g') {
        greenInfo[0] = currentRow;
        greenInfo[1] = currentColumn;
      } else if (objectArray[currentRow][currentColumn] == 'b') {
        blueInfo[0] = currentRow;
        blueInfo[1] = currentColumn;
      }
    }
  }
  return;
}
