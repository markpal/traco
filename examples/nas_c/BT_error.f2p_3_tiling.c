#pragma omp parallel for
{
  for (c4 = 1; c4 <= 5; c4 += 1)
    for (c6 = 1; c6 <= 3; c6 += 1)
      rc4s[c4]=rc4s[c4]/c6ble[gric6_pos-2];
  for (c4 = 1; c4 <= 5; c4 += 1)
    rc4s[c4]=rc4s[c4];
}
