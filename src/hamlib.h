#ifndef HAMLIB_H
#define HAMLIB_H

#include <wx/stattext.h>
#include <wx/combobox.h>
#include <vector>
extern "C" {
#include <hamlib/rig.h>
}

class Hamlib {

    public:
        Hamlib();
        ~Hamlib();
        void populateComboBox(wxComboBox *cb);
        bool connect(unsigned int rig_index, const char *serial_port, const int serial_rate, const int civ_hex = 0);
        bool ptt(bool press, wxString &hamlibError);
        void enable_mode_detection(wxStaticText* statusBox, wxTextCtrl* freqBox, bool vhfUhfMode);
        void disable_mode_detection();
        void close(void);
        int get_serial_rate(void);
        int get_data_bits(void);
        int get_stop_bits(void);
        freq_t get_frequency(void) const;
        int update_frequency_and_mode(void);
        bool isActive() const { return m_rig != nullptr; }
        
        typedef std::vector<const struct rig_caps *> riglist_t;

    private:
        static int hamlib_freq_cb(RIG* rig, vfo_t currVFO, freq_t currFreq, void* ptr);
        static int hamlib_mode_cb(RIG* rig, vfo_t currVFO, rmode_t currMode, pbwidth_t passband, void* ptr);

        void update_mode_status();

        rig_model_t m_rig_model;
        RIG *m_rig;
        /* Sorted list of rigs. */
        riglist_t m_rigList;

        /* Mode detection status box and state. */
        wxStaticText* m_modeBox;
        wxTextCtrl* m_freqBox;
        freq_t m_currFreq;
        rmode_t m_currMode;
        bool m_vhfUhfMode;
};

#endif /*HAMLIB_H*/
