import Live
import logging
from datetime import datetime
from ableton.v2.control_surface import ControlSurface, MIDI_NOTE_TYPE

LOG_FILE_PATH = '/Users/admin/rokusdev/virtual_band_2/source/openai/logfile.txt'

# Define MIDI status byte ranges
MIDI_NOTE_ON_STATUS_RANGE = range(0x90, 0xA0)  # 144-159
MIDI_NOTE_OFF_STATUS_RANGE = range(0x80, 0x90)  # 128-143

class MIDILogger(ControlSurface):
    _instance = None  # Class variable to ensure single instance
    
    def __init__(self, c_instance):
        if MIDILogger._instance is not None:
            self.show_message("MIDILogger is already initialized.")
            return

        ControlSurface.__init__(self, c_instance)
        MIDILogger._instance = self  # Set instance

        self._c_instance = c_instance
        self._song = self._c_instance.song()
        try:
            self.log_file = open(LOG_FILE_PATH, 'w')
            self.log_file.write("MIDILogger initialized. File opened successfully.\n")
            self.log_file.flush()
            self.show_message("MIDILogger: Log file opened")
            self.set_up_listeners()
        except IOError as e:
            self.show_message("Error opening log file: {}".format(e))

    def set_up_listeners(self):
        try:
            self._song.add_record_mode_listener(self.on_record_mode_changed)
            for track in self._song.tracks:
                if track.can_be_armed and track.has_midi_input:
                    self.log_file.write("name: \n\t{}\n".format(track.name))
                    self.log_file.write("can be armed: \n\t{}\n".format(str(track.can_be_armed)))
                    self.log_file.write("arm: \n\t{}\n".format(str(track.arm)))
                    self.log_file.write("clip slots: \n\t{}\n".format(str(track.clip_slots)))
                    
                    self.log_file.write("data: \n\t{}\n".format(str(track.get_data)))
                    self.log_file.write("has midi input: \n\t{}\n".format(str(track.has_midi_input))) 
                    self.log_file.write("has midi output: \n\t{}\n".format(str(track.has_midi_output))) 

                    self.log_file.write("record mode: \n\t{}\n".format(self._song.record_mode))

                    track.add_arm_listener(self.on_arm_state_changed)
                    track.add_playing_slot_index_listener(self.on_playing_slot_changed)
            self.log_file.write("MIDI note listeners added successfully\n")
                    
        except Exception as e:
            logging.info("Error setting up listeners: {}".format(e))


#    def set_up_listeners(self):
#        try:
#            self._song.add_record_mode_listener(self.on_record_mode_changed)
#        try:
#            for clip_slot in track.clip_slots:
#                if clip_slot.has_clip:
#                    clip = clip_slot.clip
#                    if clip.is_recording:
#                        logging.info(f"Monitoring clip in track {track.name}")
#                        clip.add_notes_listener(lambda: self.on_notes_changed(clip))
#        except Exception as e:
#            logging.info(f"Error in monitor_midi_clips: {e}")
#                if track.has_midi_input:
#                    self.log_file.write("name: \n\t{}\n".format(track.name))
#                    self.log_file.write("can be armed: \n\t{}\n".format(str(track.can_be_armed)))
#                    self.log_file.write("arm: \n\t{}\n".format(str(track.arm)))
#                    self.log_file.write("clip slots: \n\t{}\n".format(str(track.clip_slots)))
#                    
#                    self.log_file.write("data: \n\t{}\n".format(str(track.get_data)))
#                    self.log_file.write("has midi input: \n\t{}\n".format(str(track.has_midi_input))) 
#                    self.log_file.write("has midi output: \n\t{}\n".format(str(track.has_midi_output))) 
#
#                    self.log_file.write("record mode: \n\t{}\n".format(self._song.record_mode))
#
#                    # self.log_file.write("track:\n{}".format(str(dir(track))).replace(', ', '\n\t'))
#
#
#                    if track.can_be_armed and track.has_midi_input:
#                        track.add_arm_listener(self.on_arm_state_changed))
#                        track.add_playing_slot_index_listener(lambda: self.on_playing_slot_changed(track))
#
#            self._song.add_current_song_time_listener(self.on_current_song_time_changed)
#            self.log_file.write("MIDI note listeners added successfully\n")
#            self.log_file.flush()
#            self.show_message("MIDI note listeners added")
#        except Exception as e:
#            self.log_file.write("Error setting up listeners: {}\n".format(e))
#            self.log_file.flush()
#            self.show_message("Error: {}".format(e))
    
    def on_record_mode_changed(self):
        for track in self._song.tracks:
            if track.arm and self._song.record_mode:
                self.monitor_midi_clips(track)

    def on_arm_state_changed(self):
        try:
            for track in self._song.tracks:
                if track.arm and self._song.record_mode:
                    logging.info("Track {} armed: {}".format(track.name, track.arm))
                    self.monitor_midi_clips(track)
        except Exception as e:
            logging.info("Error in on_arm_state_changed: {}".format(e))

    def on_playing_slot_changed(self):
        try:
            for track in self._song.tracks:
                if track.arm and self._ssong.record_mode:
                    logging.info("Track {} playing slot changed".format(track.name))
                    self.monitor_midi_clips(track)
        except Exception as e:
            logging.info("Error in on_playing_slot_changed: {}".format(e))

    def monitor_midi_clips(self, track):
        try:
            for clip_slot in track.clip_slots:
                if clip_slot.has_clip:
                    clip = clip_slot.clip
                    if clip.is_recording:
                        self.log_file.write("Monitoring clip in track {}\n".format(track.name))
                        logging.info("Monitoring clip in track {}".format(track.name))
                        clip.add_notes_listener(lambda: self.on_notes_changed(clip))
        except Exception as e:
            logging.info("Error in monitor_midi_clips: {}".format(e))

    def on_notes_changed(self, clip):
        try:
            notes = clip.get_notes(0, 0, clip.length, 128)
            timestamp = datetime.now().strftime('%Y-%m-%d %H:%M:%S.%f')
            for note in notes:
                log_midi_message(note, timestamp)
        except Exception as e:
            logging.info("Error in on_notes_changed: {}".format(e))


    def on_current_song_time_changed(self):
        pass  # We need this to keep the script active, but we don't need to do anything here

    def on_midi_note_received(self, midi_bytes):
        self.log_file.write("MIDI received - Status: {}, Note: {}, Velocity: {}\n".format(midi_bytes[0], midi_bytes[1], midi_bytes[2]))
        self.log_file.flush()
        self.show_message("MIDI received")
        
        status_byte = midi_bytes[0] & 0xF0  # Mask out the channel
        if status_byte in MIDI_NOTE_ON_STATUS_RANGE:
            event_type = "Note On"
        elif status_byte in MIDI_NOTE_OFF_STATUS_RANGE:
            event_type = "Note Off"
        else:
            self.log_file.write("Unhandled MIDI status: {}\n".format(status_byte))
            self.log_file.flush()
            return
    
        note = midi_bytes[1]
        velocity = midi_bytes[2]
        timestamp = self._song.current_song_time
        self.log_note_event(note, velocity, timestamp, event_type)

    def log_midi_message(self, note, timestamp):
        try:
            log_entry = "Note: {}, Velocity: {}, Timestamp: {}\n".format(note[0], note[2], timestamp)
            self.log_file.write(log_entry)
            self.log_file.flush()
        except IOError as e:
            self.show_message("Error writing to log file: {}".format(e))

    def log_note_event(self, note, velocity, timestamp, event_type):
        if self.log_file:
            try:
                log_entry = "{}: Note {}, Velocity {}, Timestamp {}\n".format(event_type, note, velocity, timestamp)
                self.log_file.write(log_entry)
                self.show_message(log_entry.strip())
            except IOError as e:
                self.show_message("Error writing to log file: {}".format(e))

    def disconnect(self):
        if self.log_file:
            self.log_file.write("MIDILogger disconnecting.\n")
            self.log_file.flush()
            self.log_file.close()
        try:
            for track in self._song.tracks:
                if track.has_midi_input:
                    if track.arm_has_listener(self.on_arm_state_changed):
                        track.remove_arm_listener(self.on_arm_state_changed)
                    if track.playing_slot_index_has_listener(self.on_playing_slot_changed):
                        track.remove_playing_slot_index_listener(self.on_playing_slot_changed)
            if self._song.current_song_time_has_listener(self.on_current_song_time_changed):
                self._song.remove_current_song_time_listener(self.on_current_song_time_changed)
            if self._song.record_mode_has_listener(self.on_record_mode_changed):
                self._song.remove_record_mode_listener(self.on_record_mode_changed)
        except RuntimeError as e:
            self.log_file.write("Error in disconnect: {}\n".format(e))
            self.log_file.flush()
            logging.info("Error in disconnect: {}".format(e))
        ControlSurface.disconnect(self)
