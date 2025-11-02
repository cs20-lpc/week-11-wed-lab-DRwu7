// ----------------------------------------------------------------------
// BRANCH MODIFIED: insert
// ----------------------------------------------------------------------
template <typename T>
int HashTableClosed<T>::insert(const T& key)
{
    // Check if the table is full
    if (this->N >= this->M) {
        throw runtime_error("Insert failed: Hash table is full");
    }

    // The initial index is h1(key), which counts as probe 1.
    int index = this->hash1(key);
    int probes = 1;

    // Check the initial position (i=0 is implicitly probes=1)
    if (!this->occupied[index]) {
        this->table[index] = key;
        this->occupied[index] = true;
        this->N++;
        return probes;
    }

    // If the key is already present at the initial spot
    if (this->table[index] == key) {
        return probes;
    }

    // Handle collision using probing (i starts at 1)
    for (int i = 1; i < this->M; ++i) {
        index = this->probeIndex(key, i);
        probes++;
        
        if (!this->occupied[index]) {
            // Found an empty slot
            this->table[index] = key;
            this->occupied[index] = true;
            this->N++;
            return probes;
        }

        // If the key is already present in a later probed spot
        if (this->table[index] == key) {
             return probes;
        }
    }

    // Should only be reached if table is theoretically full and we exit the loop
    throw runtime_error("Insert failed: Hash table is full");
}

// ----------------------------------------------------------------------
// BRANCH MODIFIED: search
// ----------------------------------------------------------------------
template <typename T>
pair<bool, int> HashTableClosed<T>::search(const T& key) const
{
    // The initial index is h1(key), which counts as probe 1.
    int index = this->hash1(key);
    int probes = 1;
    
    // Check the initial position
    if (this->occupied[index]) {
        if (this->table[index] == key) {
            return {true, probes};
        }
    } else {
        // If the initial slot is empty, the key is not in the table
        return {false, probes};
    }
    
    // Handle probing (i starts at 1)
    for (int i = 1; i < this->M; ++i) {
        index = this->probeIndex(key, i);
        probes++;

        // If an empty slot is reached, the key is not in the table
        if (!this->occupied[index]) {
            return {false, probes};
        }
        
        // Check for a match
        if (this->table[index] == key) {
            return {true, probes};
        }
    }

    // Key not found after checking all possible slots
    return {false, probes};
}