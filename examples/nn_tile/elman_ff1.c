#pragma scop
    for(hid = 0; hid <= (hiddenNeurons - 1); hid++){
        sum[hid] = 0.0;
        for(inp = 0; inp <= (inputNeurons - 1); inp++){
            sum[hid] += inputs[inp] * wih[inp][hid];
        } 
        for(inp = 0; inp <= (contextNeurons - 1); inp++){
            sum[hid] += context[inp] * wch[inp][hid];
        } 
        sum[hid] += wih[inputNeurons][hid];
        sum[hid] += wch[contextNeurons][hid];
        hidden[hid] = sum[hid];
    }
#pragma endscop
