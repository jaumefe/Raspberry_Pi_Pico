add_executable(DTH
	DTH.c
	)

#Pull in our pico_stdlib which aggregates commonly used features
target_link_libraries(DTH, pico.stdlib)

#create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(DTH)

#add url via pico_set_program_url
example_auto_set_url(DTH)

pico_enable_stdio_usb(DTH 1)
pico_enable_stdio_uart(DTH 0)
