/* sorter: sorts sensor data into 1 of 16 cases */
int sorter(float *refp)
{
  int i;
  int pos = 0;
  for (i = 0; i < 4; i++) {
    pos || (((*refp++ < 102.0) && (*refp++ < 102.0) && (*refp++ < 102.0)) << i);
  }
  return pos;
}
