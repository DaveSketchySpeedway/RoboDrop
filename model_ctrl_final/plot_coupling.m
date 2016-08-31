% plot frequency response magnitude from each input to output
% a b c d needs to be continuous
% in, out needs to be cell array 



function [] = plot_coupling(a,b,c,d,in,out,phase_flag,fmin,fmax,resolution)


omega = logspace(fmin,fmax,resolution); % hz
omega = omega * 2 * pi(); % rad/s

n = size(a,1);
m = size(b,2);
p = size(c,1);

s = tf('s');
transfer_functions = d + c*inv(eye(size(a))*s - a) * b;

for i = 1:p
    for j = 1:m
        [mag, phase] = bode(transfer_functions(i,j), omega);
        mag = squeeze(mag);
        phase = squeeze(phase);
        
        if (phase_flag == 1)
            subplot(p*2, m, m*2*(i-1)+j)
        else
            subplot(p, m, m*(i-1)+j)
        end
        semilogx(omega/2/pi(), 20*log10(mag), 'b') % db vs hz
        hold on
        ylabel('Magnitude dB')
        xlim([10^fmin, 10^fmax])
        grid minor
        legend(['input' num2str(j) ' --> output' num2str(i)]);
        
        
        if (phase_flag == 1)
            subplot(p*2, m, m*(2*i-1)+j)
            semilogx(omega/2/pi(), phase, 'r') % deg vs hz
            hold on
            ylabel('Phase Deg')
            xlim([10^fmin, 10^fmax])
            grid minor
        legend(['input' num2str(j) ' --> output' num2str(i)]);
        else
%             title([out(i) ' actuated by ' in(j)], 'interpreter', 'none')
        end
        xlabel('Frequency Hz')
    end
end


% all_axes = findobj(gcf,'type','axes');
% linkaxes(all_axes);
        

