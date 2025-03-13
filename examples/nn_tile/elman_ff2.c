 for(out = 0; out <= (outputNeurons - 1); out++){
    sum[out] = 0.0;
        for(hid = 0; hid <= (hiddenNeurons - 1); hid++){
            sum[out] += hidden[hid] * who[hid][out];
        } 
        sum[out] += who[hiddenNeurons][out];
        actual[out] = sum[out];
    }
